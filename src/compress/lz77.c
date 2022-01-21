
#include "libccc.h"
//#include "libccc/compress/lz77.h"

#if 0 // WIP, porting from old C# code

t_s32 const BLOCK_SIZE = 0x8;
t_s32 const BUFFER_SIZE = 0x12;
t_s32 const WINDOW_SIZE = 0x1000;



/// <summary>
/// Returns the length of the compressed data once decomrpessed, or `0` if can't be decompressed
/// </summary>
t_size LZ77_GetLength(t_u8* data)
{
	if ((*data) != 0x10)
		return (0);

	t_u32 decomp_length = Core.ReadData(data, 4).GetUInt32(0, true) & 0x00FFFFFF;
	t_s32 decomp_parse = 0;
	t_u8* parse = data + 4;

	while (decomp_parse < decomp_length)
	{
		t_u8 is_compressed = (*parse);
		parse += 1;
		for (t_s32 i = 0; i < BLOCK_SIZE && decomp_parse < decomp_length; i++)
		{
			if ((is_compressed & 0x80) != 0)
			{
				t_u8 amount = (t_u8)((((*parse) >> 4) & 0xF) + 3);
				t_u16 position = (t_u16)(((((*parse) & 0xF) << 8) + (*parse)) + 1);

				if (position > decomp_parse)
					return (0);

				decomp_parse += amount;
				parse += 2;
			}
			else
			{
				decomp_parse++;
				parse += 1;
			}
			is_compressed <<= 1;
		}
	}
	if (parse % 4 != 0)
		parse += 4 - parse % 4;
	return ((t_size)(parse - data));
}

/// <summary>
/// Decompress the given byte array holding GBA formatted LZ77 data
/// </summary>
t_u8[] LZ77_Decompress(t_u8* address)
{
	t_u8* pos = address;
	if (address == new t_u8*())
		return null;
	else if ((*pos) != 0x10)
		throw new Exception("LZ77 compressed data is not valid, it should start with 0x10");
	pos += 1;

	t_s32 offset = 0;
	t_s32 length = (*pos) + ((*pos + 1) << 8) + ((*pos + 2) << 16);
	pos += 3;

	t_u8[] result = new t_u8[length];

	t_u8 is_compressed;
	try
	{
		while (offset < length)
		{
			is_compressed = (*pos);
			pos += 1;
			// byte of 8 flags for 8 blocks
			for (t_s32 i = 0; i < BLOCK_SIZE; i++)
			{
				if ((is_compressed & (0x80 >> i)) == 0)
				{   // so this block isn't compressed, copy a single byte
					result[offset++] = (*pos);
					pos += 1;
				}
				else
				{
					t_u16 block = (t_u16)pos[0] | (pos[1] << 8));
					pos += 2;
					// load LZ copy block
					t_s32 amountToCopy = ((block >> 4) & 0xF) + 3;
					t_s32 displacement = ((block & 0xF) << 8) | ((block >> 8) & 0xFF);

					t_s32 copyPosition = offset - displacement - 1;
					if (copyPosition > length) throw new Exception();

					for (t_s32 j = 0; j < amountToCopy; j++)
					{
						t_u8 b = result[copyPosition + j];
						result[offset++] = b;
					}
				}

				if (offset >= length) break;
			}
		}
	}
	catch
	{
		return result;
	}
	return result;
}



/// <summary>
/// Returns info about the result of an LZ77 compression search given the array to search through,
/// the position to search from, and the length of array that is being compressed.
/// </summary>
t_s32[] LZ77_Search(t_u8[] input, t_s32 position, t_s32 length)
{
	List<t_s32> results = new List<t_s32>();

	if (!(position < length))
		return new t_s32[] { -1, 0 };
	if (position < 3 || (length - position) < 3)
		return new t_s32[] { 0, 0 };

	for (t_s32 i = 1; ((i < WINDOW_SIZE) && (i < position)); i++)
	{
		if (input[position - i - 1] == input[position])
		{
			results.Add(i + 1);
		}
	}
	if (results.Count == 0)
		return new t_s32[] { 0, 0 };

	t_s32 amountOfBytes = 0;

	while (amountOfBytes < BUFFER_SIZE)
	{
		amountOfBytes++;
		Boolean searchComplete = false;
		for (t_s32 i = results.Count - 1; i >= 0; i--)
		{
			try
			{
				if (input[position + amountOfBytes] !=
					input[position + (amountOfBytes % results[i]) - results[i]])
				{
					if (results.Count > 1)
						results.RemoveAt(i);
					else
						searchComplete = true;
				}
			}
			catch
			{
				return new t_s32[] { 0, 0 };
			}
		}
		if (searchComplete)
			break;
	}

	//Length of data is first, then position
	return new t_s32[] { amountOfBytes, results[0] };
}

/// <summary>
/// Returns the given byte array, compressed using the LZ77 compression algorithm
/// </summary>
t_u8[] LZ77_Compress(t_u8[] input)
{
	t_s32 length = input.Length;
	t_s32 position = 0;

	List<t_u8> result = new List<t_u8>();
	result.Add((t_u8)0x10);

	result.Add((t_u8)(0xFF & (length)));
	result.Add((t_u8)(0xFF & (length >> 8)));
	result.Add((t_u8)(0xFF & (length >> 16)));

	t_u8 is_compressed = 0;
	t_s32[] searchResult = null;
	t_u8 add = (t_u8)0;
	List<t_u8> tempList = null;

	while (position < length)
	{
		is_compressed = 0;
		tempList = new List<t_u8>();

		for (t_s32 i = 0; i < BLOCK_SIZE; i++)
		{
			searchResult = LZ77_Search(input, position, length);

			if (searchResult[0] > 2)
			{
				add = (t_u8)((((searchResult[0] - 3) & 0xF) << 4) + (((searchResult[1] - 1) >> 8) & 0xF));
				tempList.Add(add);
				add = (t_u8)((searchResult[1] - 1) & 0xFF);
				tempList.Add(add);
				position += searchResult[0];
				is_compressed |= (t_u8)(1 << (BLOCK_SIZE - (i + 1)));
			}
			else if (searchResult[0] >= 0)
			{
				tempList.Add(input[position++]);
			}
			else break;
		}

		result.Add(is_compressed);
		result.AddRange(tempList);
	}

	while (result.Count % 4 != 0)
	{
		result.Add(0);
	}

	return result.ToArray();
}

#endif
