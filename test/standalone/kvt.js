// This file holds a script to test KVT struct conversion via the emscripten heap

let module_factory = require("./libccc.js");
module_factory().then((emjs) =>
{
	console.log("Emscripten module is ready to use");

// C utils

const kvt_structsize = 24;
const kvt_structinfo =
[
	["next",  "s_kvt*",    "*",    0, 4],
	["prev",  "s_kvt*",    "*",    4, 4],
	["key",   "t_utf8*",   "*",    8, 4],
	["type",  "t_dynamic", "i32", 12, 4],
	["value", "u_dynamic", "i64", 16, 8],
];

let DYNAMICTYPE_INVALID	= (0);		//!< value stored is invalid
let DYNAMICTYPE_NULL	= (1 << 0);	//!< no value stored
let DYNAMICTYPE_BOOLEAN	= (1 << 1);	//!< value stored as boolean (`t_bool`)
let DYNAMICTYPE_INTEGER	= (1 << 2);	//!< value stored as integer (`t_s64`)
let DYNAMICTYPE_FLOAT	= (1 << 3);	//!< value stored as floating-point number: (`t_f64`)
let DYNAMICTYPE_STRING	= (1 << 4);	//!< value stored as string (`t_char*`)
let DYNAMICTYPE_ARRAY	= (1 << 5);	//!< value stored as array of values (no keys)
let DYNAMICTYPE_OBJECT	= (1 << 6);	//!< value stored as dict of values (with keys)
let DYNAMICTYPE_RAW		= (1 << 7);	//!< value stored as raw string (language-specific syntax)

let DYNAMICTYPE_ISREFERENCE	= (1 << 8);	//!< If this bit is set, the `value` is not to be freed



// JS utils

/** returns `true` if given value is of type "array" */
let isArray = function(x)
{
    return (!!x) && (x.constructor === Array);
};

/** returns `true` if given value is of type "object" */
let isObject = function(x)
{
    return (!!x) && (x.constructor === Object);
};

/** performs a deep equality check between two values */
function deepEquals(a, b)
{
	if (a === b)
		return true;
	else if (a == null)
		return false;
	else if (b == null)
		return false;
	else if (Object.keys(a).length !== Object.keys(b).length)
		return false;
	for (const key in a)
	{
		const a_value = a[key]
		const b_value = b[key]
		// If the value is an object, recursively check if they're different objects
		// If it isn't, uses !== to check
		if ((a_value instanceof Object && !deepEquals(a_value, b_value)) ||
			(!(a_value instanceof Object) && a_value !== b_value))
			return false;
	}
	return true
}



// actual function implems

function JSON_Decode(json_string)
{
	function kvt_to_jso(result, kvt)
	{
		let tmp;
/*
		console.log("====== kvt: ", Number(kvt).toString(16));
		for (let i = 0; i <= 6; ++i)
		{
			console.log("offset:" + Number(kvt + i * 4).toString(16) + "\t| ",
				Number(emjs.HEAPU32[kvt/4 + i]).toString(16));
		}
*/
		let next = emjs.HEAPU32[kvt/4 + 0];
		let prev = emjs.HEAPU32[kvt/4 + 1];
		tmp      = emjs.HEAPU32[kvt/4 + 2];	let key = (tmp > 0) ? emjs.UTF8ToString(tmp) : null;
		tmp      = emjs.HEAPU32[kvt/4 + 3];	let type = tmp;
		tmp      = emjs.HEAPU32[kvt/4 + 4];	let value = undefined;
		let is_ref = ((type & DYNAMICTYPE_ISREFERENCE) === 1 ? true : false);
		type &= ~DYNAMICTYPE_ISREFERENCE;
		if      (type === DYNAMICTYPE_INVALID) { value = undefined; } //throw "Invalid type in KVT struct (at key: '" + key + "')"; }
		else if (type === DYNAMICTYPE_NULL)    { value = null; }
		else if (type === DYNAMICTYPE_BOOLEAN) { value = (emjs.HEAPU8[kvt + 16] == 0 ? false : true); }
		else if (type === DYNAMICTYPE_INTEGER) { value =  emjs.HEAP64[kvt/8 + 2]; }
		else if (type === DYNAMICTYPE_FLOAT)   { value = emjs.HEAPF64[kvt/8 + 2]; }
		else if (type === DYNAMICTYPE_STRING)  { value = (tmp > 0) ? emjs.UTF8ToString(tmp) : null; }
		else if (type === DYNAMICTYPE_ARRAY)   { value = kvt_to_jso([], tmp); }
		else if (type === DYNAMICTYPE_OBJECT)  { value = kvt_to_jso({}, tmp); }
		else if (type === DYNAMICTYPE_RAW)     { value = JSON.parse(emjs.UTF8ToString(tmp)); }
/*
		console.log("DEBUG: " + Number(kvt).toString() + "\n",
		{
			next:  next,
			prev:  prev,
			key:   key,
			type:  type,
			isref: is_ref,
			value: value,
		});
*/
		if (result == null) // root-level
		{
			if      (type === DYNAMICTYPE_INVALID) { result = undefined; } //throw "Invalid type in KVT struct (at key: '" + key + "')"; }
			else if (type === DYNAMICTYPE_NULL)    { result = null; }
			else if (type === DYNAMICTYPE_BOOLEAN) { result = (emjs.HEAPU8[kvt + 16] == 0 ? false : true); }
			else if (type === DYNAMICTYPE_INTEGER) { result =  emjs.HEAP64[kvt/8 + 2]; }
			else if (type === DYNAMICTYPE_FLOAT)   { result = emjs.HEAPF64[kvt/8 + 2]; }
			else if (type === DYNAMICTYPE_STRING)  { result = (tmp > 0) ? emjs.UTF8ToString(tmp) : null; }
			else if (type === DYNAMICTYPE_ARRAY)   { result = []; value = kvt_to_jso(result, tmp); }
			else if (type === DYNAMICTYPE_OBJECT)  { result = {}; value = kvt_to_jso(result, tmp); }
			else if (type === DYNAMICTYPE_RAW)     { result = JSON.parse(emjs.UTF8ToString(tmp)); }
		}
		else
		{
			if (key == null || key.length === 0)
				result.push(value);
			else result[key] = value;
		}
		if (next != null && next > 0)
		{
			value = kvt_to_jso(result, next);
		}
		return result;
	}

	let ptr = emjs.ccall(
		"JSON_FromString_Lenient", // name of C function
		"number", // return type
		["string"], // argument types
		[json_string]);
	let result = kvt_to_jso(null, ptr);
	emjs.ccall(
		"KVT_Delete", // name of C function
		null, // return type
		["number"], // argument types
		[ptr]);
	return result;
}



function JSON_Encode(json_object)
{
	function jso_to_kvt(result, jso)
	{
		if (jso == undefined)
			return 0;
		let length;
		let c_str;
		let kvt = emjs._malloc(kvt_structsize);
		if (jso == null)
		{
			emjs.HEAPU32[kvt/4 + 3] = DYNAMICTYPE_NULL;
			emjs.HEAPU64[kvt/8 + 2] = 0;
		}
		else if (isArray(jso))
		{
			emjs.HEAPU32[kvt/4 + 3] = DYNAMICTYPE_ARRAY;
			let prev = 0;
			let first = null;
			let current = null;
			for (const value of jso)
			{
				current = jso_to_kvt(kvt, value);
				emjs.HEAPU32[current/4 + 0] = 0;
				emjs.HEAPU32[current/4 + 1] = prev;
				emjs.HEAPU32[current/4 + 2] = 0; // set 'key' to NULL
				if (first == null)
					first = current;
				if (prev > 0) emjs.HEAPU32[prev/4] = current; // set 'next'
				prev = current;
			}
			emjs.HEAPU32[first/4 + 1] = current; // set first 'prev' to point to end of linked list
			emjs.HEAPU32[kvt/4 + 4] = first;
		}
		else if (isObject(jso))
		{
			emjs.HEAPU32[kvt/4 + 3] = DYNAMICTYPE_OBJECT;
			let prev = 0;
			let first = null;
			let current = null;
			for (const [key, value] of Object.entries(jso))
			{
				current = jso_to_kvt(kvt, value);
				emjs.HEAPU32[current/4 + 0] = 0;
				emjs.HEAPU32[current/4 + 1] = prev;
				length = emjs.lengthBytesUTF8(key) + 1;
				c_str = emjs._malloc(length);
				emjs.stringToUTF8(key, c_str, length);
				emjs.HEAPU32[current/4 + 2] = c_str; // set 'key'
				if (first == null)
					first = current;
				if (prev > 0) emjs.HEAPU32[prev/4] = current; // set 'next'
				prev = current;
			}
			emjs.HEAPU32[first/4 + 1] = current; // set first 'prev' to point to end of linked list
			emjs.HEAPU32[kvt/4 + 4] = first;
		}
		else if (typeof jso === "boolean")
		{
			emjs.HEAPU32[kvt/4 + 3] = DYNAMICTYPE_BOOLEAN;
			emjs.HEAPU8[kvt + 16] = (jso ? 1 : 0);
		}
		else if (typeof jso === "number")
		{
			emjs.HEAPU32[kvt/4 + 3] = DYNAMICTYPE_FLOAT;
			emjs.HEAPF64[kvt/8 + 2] = jso;
		}
		else if (typeof jso === "bigint")
		{
			emjs.HEAPU32[kvt/4 + 3] = DYNAMICTYPE_INTEGER;
			emjs.HEAP64 [kvt/8 + 2] = jso;
		}
		else if (typeof jso === "string")
		{
			length = emjs.lengthBytesUTF8(jso) + 1;
			c_str = emjs._malloc(length);
			emjs.stringToUTF8(jso, c_str, length);
			emjs.HEAPU32[kvt/4 + 3] = DYNAMICTYPE_STRING;
			emjs.HEAPU32[kvt/4 + 4] = c_str;
		}
		else
		{
			emjs.HEAPU32[kvt/4 + 3] = DYNAMICTYPE_INVALID;
			emjs.HEAPU64[kvt/8 + 2] = 0;
		}
		// root-level
		if (result == null)
		{
			emjs.HEAPU32[kvt/4 + 0] = 0;
			emjs.HEAPU32[kvt/4 + 1] = 0;
			emjs.HEAPU32[kvt/4 + 2] = 0;
		}
		result = kvt;
/*
		console.log("====== kvt: ", Number(kvt).toString(16));
		for (let i = 0; i <= 6; ++i)
		{
			console.log("offset:" + Number(kvt + i * 4).toString(16) + "\t| ",
				Number(emjs.HEAPU32[kvt/4 + i]).toString(16));
		}
*/
		return result;
	}

	let ptr = jso_to_kvt(null, json_object);
	let result = emjs.ccall(
		"JSON_ToString_Minify", // name of C function
		"string", // return type
		["number"], // argument types
		[ptr]); // arguments
	emjs.ccall(
		"KVT_Delete", // name of C function
		null, // return type
		["number"], // argument types
		[ptr]);
	return result;
}



// Tests

let test ="{\"Label\":\"Entity Label\",\"Attributes\":{\"EXAMPLE_ATTRIBUTE\":[{\"Values\":[\"\",{\"AVESTERRA\":\"Example\"},{\"ENTITY\":\"<0|0|24>\"},{\"BOOLEAN\":\"TRUE\"},{\"CHARACTER\":\"A\"},{\"STRING\":\"Hello World!\\u0007\"},{\"TEXT\":\"ÅvësTêrrã\"},{\"WEB\":\"www.example.com\"},{\"INTERCHANGE\":\"{\\\"Greeting\\\":\\\"Hello World!\\u0007\\\"}\"},{\"INTEGER\":\"42\"},{\"FLOAT\":\"3.14159000000000000E+00\"},{\"TIME\":\"1263186022\"},{\"DATA\":\"4142434445464748494A4B4C4D4E4F505152535455565758595A3031323334353637383921402324255E262A28295F2B2C2E3B273C3E3F3A602D3D\"},{\"EXCEPTION\":\"{\\\"ERROR\\\": \\\"HALT_ERROR\\\",\\\"MESSAGE\\\": \\\"The machine has halted\\\"}\"},{\"OPERATOR\":\"HALT_OPERATOR\"},{\"FUNCTION\":\"<0|0|18>\"},{\"MEASUREMENT\":\"{\\\"FLOAT\\\": 4.20000000000000E+01,\\\"UNIT\\\": \\\"GRAM_UNIT\\\",\\\"PREFIX\\\": \\\"MICRO_PREFIX\\\",\\\"CONFIDENCE\\\": 9.99000000000000E+01,\\\"UNCERTAINTY\\\": 1.00000000000000E-01}\"},{\"LOCUTOR\":\"{\\\"ENTITY\\\": \\\"<0|0|24>\\\",\\\"OUTLET\\\": \\\"<0|0|24>\\\",\\\"AUXILIARY\\\": \\\"<0|0|1>\\\",\\\"ANCILLARY\\\": \\\"<0|0|2>\\\",\\\"CONTEXT\\\": \\\"AVESTERRA_CONTEXT\\\",\\\"CATEGORY\\\": \\\"AVESTERRA_CATEGORY\\\",\\\"CLASS\\\": \\\"AVESTERRA_CLASS\\\",\\\"METHOD\\\": \\\"AVESTERRA_METHOD\\\",\\\"ATTRIBUTE\\\": \\\"AVESTERRA_ATTRIBUTE\\\",\\\"INSTANCE\\\": 1,\\\"NAME\\\": \\\"Example Name\\\",\\\"VALUE\\\": \\\"Example String\\\",\\\"VALUE_TAG\\\": \\\"STRING_TAG\\\",\\\"INDEX\\\": 1,\\\"COUNT\\\": 123,\\\"PRECEDENCE\\\": \\\"AVESTERRA_PRECEDENCE\\\",\\\"PARAMETER\\\": -1,\\\"MODE\\\": \\\"AVESTERRA_MODE\\\",\\\"EVENT\\\": \\\"AVESTERRA_EVENT\\\",\\\"TIMEOUT\\\": 60,\\\"ASPECT\\\": \\\"AVESTERRA_ASPECT\\\",\\\"AUTHORITY\\\": \\\"********-****-****-****-************\\\"}\"}]},{\"Label\":\"Attribute Label\",\"Properties\":[[\"Null Attribute Property\",\"Null\",\"\"],[\"AvesTerra Attribute Property\",\"AvesTerra\",{\"AVESTERRA\":\"Example\"}],[\"Entity Attribute Property\",\"Entity\",{\"ENTITY\":\"<0|0|24>\"}],[\"Boolean Attribute Property\",\"Boolean\",{\"BOOLEAN\":\"TRUE\"}],[\"Character Attribute Property\",\"Character\",{\"CHARACTER\":\"A\"}],[\"String Attribute Property\",\"String\",{\"STRING\":\"Hello World!\\u0007\"}],[\"Text Attribute Property\",\"Text\",{\"TEXT\":\"ÅvësTêrrã\"}],[\"Web Attribute Property\",\"Web\",{\"WEB\":\"www.example.com\"}],[\"Interchange Attribute Property\",\"Interchange\",{\"INTERCHANGE\":\"{\\\"Greeting\\\":\\\"Hello World!\\u0007\\\"}\"}],[\"Integer Attribute Property\",\"Integer\",{\"INTEGER\":\"42\"}],[\"Float Attribute Property\",\"Float\",{\"FLOAT\":\"3.14159000000000000E+00\"}],[\"Time Attribute Property\",\"Time\",{\"TIME\":\"1263186022\"}],[\"Data Attribute Property\",\"Data\",{\"DATA\":\"4142434445464748494A4B4C4D4E4F505152535455565758595A3031323334353637383921402324255E262A28295F2B2C2E3B273C3E3F3A602D3D\"}],[\"Exception Attribute Property\",\"Exception\",{\"EXCEPTION\":\"{\\\"ERROR\\\": \\\"HALT_ERROR\\\",\\\"MESSAGE\\\": \\\"The machine has halted\\\"}\"}],[\"Operator Attribute Property\",\"Operator\",{\"OPERATOR\":\"HALT_OPERATOR\"}],[\"Function Attribute Property\",\"Function\",{\"FUNCTION\":\"<0|0|18>\"}],[\"Measurement Attribute Property\",\"Measurement\",{\"MEASUREMENT\":\"{\\\"FLOAT\\\": 4.20000000000000E+01,\\\"UNIT\\\": \\\"GRAM_UNIT\\\",\\\"PREFIX\\\": \\\"MICRO_PREFIX\\\",\\\"CONFIDENCE\\\": 9.99000000000000E+01,\\\"UNCERTAINTY\\\": 1.00000000000000E-01}\"}],[\"Locutor Attribute Property\",\"Locutor\",{\"LOCUTOR\":\"{\\\"ENTITY\\\": \\\"<0|0|24>\\\",\\\"OUTLET\\\": \\\"<0|0|24>\\\",\\\"AUXILIARY\\\": \\\"<0|0|1>\\\",\\\"ANCILLARY\\\": \\\"<0|0|2>\\\",\\\"CONTEXT\\\": \\\"AVESTERRA_CONTEXT\\\",\\\"CATEGORY\\\": \\\"AVESTERRA_CATEGORY\\\",\\\"CLASS\\\": \\\"AVESTERRA_CLASS\\\",\\\"METHOD\\\": \\\"AVESTERRA_METHOD\\\",\\\"ATTRIBUTE\\\": \\\"AVESTERRA_ATTRIBUTE\\\",\\\"INSTANCE\\\": 1,\\\"NAME\\\": \\\"Example Name\\\",\\\"VALUE\\\": \\\"Example String\\\",\\\"VALUE_TAG\\\": \\\"STRING_TAG\\\",\\\"INDEX\\\": 1,\\\"COUNT\\\": 123,\\\"PRECEDENCE\\\": \\\"AVESTERRA_PRECEDENCE\\\",\\\"PARAMETER\\\": -1,\\\"MODE\\\": \\\"AVESTERRA_MODE\\\",\\\"EVENT\\\": \\\"AVESTERRA_EVENT\\\",\\\"TIMEOUT\\\": 60,\\\"ASPECT\\\": \\\"AVESTERRA_ASPECT\\\",\\\"AUTHORITY\\\": \\\"********-****-****-****-************\\\"}\"}]]}]},\"Properties\":[[\"Null Entity Property\",\"Null\",\"\"],[\"AvesTerra Entity Property\",\"AvesTerra\",{\"AVESTERRA\":\"Example\"}],[\"Entity Entity Property\",\"Entity\",{\"ENTITY\":\"<0|0|24>\"}],[\"Boolean Entity Property\",\"Boolean\",{\"BOOLEAN\":\"TRUE\"}],[\"Character Entity Property\",\"Character\",{\"CHARACTER\":\"A\"}],[\"String Entity Property\",\"String\",{\"STRING\":\"Hello World!\\u0007\"}],[\"Text Entity Property\",\"Text\",{\"TEXT\":\"ÅvësTêrrã\"}],[\"Uniform Entity Property\",\"Uniform\",{\"WEB\":\"www.example.com\"}],[\"Interchange Entity Property\",\"Interchange\",{\"INTERCHANGE\":\"{\\\"Greeting\\\":\\\"Hello World!\\u0007\\\"}\"}],[\"Integer Entity Property\",\"Integer\",{\"INTEGER\":\"42\"}],[\"Float Entity Property\",\"Float\",{\"FLOAT\":\"3.14159000000000000E+00\"}],[\"Time Entity Property\",\"Time\",{\"TIME\":\"1263186022\"}],[\"Data Entity Property\",\"Data\",{\"DATA\":\"4142434445464748494A4B4C4D4E4F505152535455565758595A3031323334353637383921402324255E262A28295F2B2C2E3B273C3E3F3A602D3D\"}],[\"Exception Entity Property\",\"Exception\",{\"EXCEPTION\":\"{\\\"ERROR\\\": \\\"HALT_ERROR\\\",\\\"MESSAGE\\\": \\\"The machine has halted\\\"}\"}],[\"Operator Entity Property\",\"Operator\",{\"OPERATOR\":\"HALT_OPERATOR\"}],[\"Function Entity Property\",\"Function\",{\"FUNCTION\":\"<0|0|18>\"}],[\"Measurenent Entity Property\",\"Measurement\",{\"MEASUREMENT\":\"{\\\"FLOAT\\\": 4.20000000000000E+01,\\\"UNIT\\\": \\\"GRAM_UNIT\\\",\\\"PREFIX\\\": \\\"MICRO_PREFIX\\\",\\\"CONFIDENCE\\\": 9.99000000000000E+01,\\\"UNCERTAINTY\\\": 1.00000000000000E-01}\"}],[\"Locutor Entity Property\",\"Locutor\",{\"LOCUTOR\":\"{\\\"ENTITY\\\": \\\"<0|0|24>\\\",\\\"OUTLET\\\": \\\"<0|0|24>\\\",\\\"AUXILIARY\\\": \\\"<0|0|1>\\\",\\\"ANCILLARY\\\": \\\"<0|0|2>\\\",\\\"CONTEXT\\\": \\\"AVESTERRA_CONTEXT\\\",\\\"CATEGORY\\\": \\\"AVESTERRA_CATEGORY\\\",\\\"CLASS\\\": \\\"AVESTERRA_CLASS\\\",\\\"METHOD\\\": \\\"AVESTERRA_METHOD\\\",\\\"ATTRIBUTE\\\": \\\"AVESTERRA_ATTRIBUTE\\\",\\\"INSTANCE\\\": 1,\\\"NAME\\\": \\\"Example Name\\\",\\\"VALUE\\\": \\\"Example String\\\",\\\"VALUE_TAG\\\": \\\"STRING_TAG\\\",\\\"INDEX\\\": 1,\\\"COUNT\\\": 123,\\\"PRECEDENCE\\\": \\\"AVESTERRA_PRECEDENCE\\\",\\\"PARAMETER\\\": -1,\\\"MODE\\\": \\\"AVESTERRA_MODE\\\",\\\"EVENT\\\": \\\"AVESTERRA_EVENT\\\",\\\"TIMEOUT\\\": 60,\\\"ASPECT\\\": \\\"AVESTERRA_ASPECT\\\",\\\"AUTHORITY\\\": \\\"********-****-****-****-************\\\"}\"}],[\"Annotation Entity Property\",\"Annotation\",\"\",{\"EXAMPLE_ATTRIBUTE\":\"\"}]],\"Values\":[\"\",{\"AVESTERRA\":\"Example\"},{\"ENTITY\":\"<0|0|24>\"},{\"BOOLEAN\":\"TRUE\"},{\"CHARACTER\":\"A\"},{\"STRING\":\"Hello World!\\u0007\"},{\"TEXT\":\"ÅvësTêrrã\"},{\"WEB\":\"www.example.com\"},{\"INTERCHANGE\":\"{\\\"Greeting\\\":\\\"Hello World!\\u0007\\\"}\"},{\"INTEGER\":\"42\"},{\"FLOAT\":\"3.14159000000000000E+00\"},{\"TIME\":\"1263186022\"},{\"DATA\":\"4142434445464748494A4B4C4D4E4F505152535455565758595A3031323334353637383921402324255E262A28295F2B2C2E3B273C3E3F3A602D3D\"},{\"EXCEPTION\":\"{\\\"ERROR\\\": \\\"HALT_ERROR\\\",\\\"MESSAGE\\\": \\\"The machine has halted\\\"}\"},{\"OPERATOR\":\"HALT_OPERATOR\"},{\"FUNCTION\":\"<0|0|18>\"},{\"MEASUREMENT\":\"{\\\"FLOAT\\\": 4.20000000000000E+01,\\\"UNIT\\\": \\\"GRAM_UNIT\\\",\\\"PREFIX\\\": \\\"MICRO_PREFIX\\\",\\\"CONFIDENCE\\\": 9.99000000000000E+01,\\\"UNCERTAINTY\\\": 1.00000000000000E-01}\"},{\"LOCUTOR\":\"{\\\"ENTITY\\\": \\\"<0|0|24>\\\",\\\"OUTLET\\\": \\\"<0|0|24>\\\",\\\"AUXILIARY\\\": \\\"<0|0|1>\\\",\\\"ANCILLARY\\\": \\\"<0|0|2>\\\",\\\"CONTEXT\\\": \\\"AVESTERRA_CONTEXT\\\",\\\"CATEGORY\\\": \\\"AVESTERRA_CATEGORY\\\",\\\"CLASS\\\": \\\"AVESTERRA_CLASS\\\",\\\"METHOD\\\": \\\"AVESTERRA_METHOD\\\",\\\"ATTRIBUTE\\\": \\\"AVESTERRA_ATTRIBUTE\\\",\\\"INSTANCE\\\": 1,\\\"NAME\\\": \\\"Example Name\\\",\\\"VALUE\\\": \\\"Example String\\\",\\\"VALUE_TAG\\\": \\\"STRING_TAG\\\",\\\"INDEX\\\": 1,\\\"COUNT\\\": 123,\\\"PRECEDENCE\\\": \\\"AVESTERRA_PRECEDENCE\\\",\\\"PARAMETER\\\": -1,\\\"MODE\\\": \\\"AVESTERRA_MODE\\\",\\\"EVENT\\\": \\\"AVESTERRA_EVENT\\\",\\\"TIMEOUT\\\": 60,\\\"ASPECT\\\": \\\"AVESTERRA_ASPECT\\\",\\\"AUTHORITY\\\": \\\"********-****-****-****-************\\\"}\"}],\"Data\":[\"(59 bytes)\"]}";

/*
let test =
"{" +
"\n	\"test_bool_0\": false," +
"\n	\"test_bool_1\": true," +
"\n	\"test_number\": 3.14," +
"\n	\"test_string\": \"abc\"," +
"\n	\"test_arrays\": " +
"\n	[" +
"\n		false," +
"\n		true," +
"\n		69," +
"\n		\"abcd\"" +
"\n	]," +
"\n	\"test_object\": " +
"\n	{" +
"\n		\"nest_bool_0\": false," +
"\n		\"nest_bool_1\": true," +
"\n		\"nest_number\": 420," +
"\n		\"nest_string\": \"swag\"," +
"\n		\"nest_arrays\": " +
"\n		[" +
"\n			123456," +
"\n			\"hello\"" +
"\n		]," +
"\n		\"nest_object\": null" +
"\n	}" +
"\n}" +
"\n";
*/
/*
let test =
{
	"test_bool_0": false,
	"test_bool_1": true,
	"test_number": 3.14,
	"test_string": "abc",
	"test_arrays": [
		false,
		true,
		69,
		"abcd"
	],
	"test_object": {
		"nest_bool_0": false,
		"nest_bool_1": true,
		"nest_number": 420,
		"nest_string": "swag",
		"nest_arrays": 
		[
			123456,
			"hello"
		],
		"nest_object": null
	}
};
*/

console.log("=== test ===\n", test);

let test_json = JSON_Decode(test);
console.log("=== parse ===\n", test_json);

let test_str = JSON_Encode(test_json);
console.log("=== print ===\n", test_str);

if (deepEquals(test_json, JSON_Decode(test_str)))
	console.log("Round trip conversion successful");
else console.log("Round trip conversion failed");

});
