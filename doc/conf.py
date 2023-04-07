# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys



# -- Project information -----------------------------------------------------

project = 'libccc'
copyright = 'Free & Open Source: MIT License'
author = "Alexis Duquesne, Tristan Duquesne"

# The full version, including alpha/beta/rc tags
release = "?"
with open("../VERSION") as f:
    release = f.readline() # only keep the first line of the VERSION file



# -- General configuration ---------------------------------------------------

# sys.path.insert(0, os.path.abspath("."))

# Folder path to Doxyrest extension:
sys.path.insert(1, os.path.abspath("_doxyrest/sphinx/"))
doxyrest_tab_width = 4 # Specify the size of tab indentation:
# To have macros display their value/expansion, paste the follow line of code to line 490 of _doxyrest/frame/cfamily/utils.lua:
#	s = s .. '\t' .. getLinkedTextString(define.initializer, false)

# Folder path to Breathe extension:
#sys.path.append(os.path.abspath("breathe"))
#breathe_projects = { "libccc": os.path.abspath("xml/") }
#breathe_default_project = "libccc"

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named "sphinx.ext.*") or your custom
# ones.
extensions = [
#	"breathe",
	"doxyrest",
	"cpplexer",
    "sphinx.ext.intersphinx",
    "sphinx.ext.autodoc",
    "sphinx.ext.mathjax",
    "sphinx.ext.viewcode",
	"sphinx.ext.graphviz"]

# Add any paths that contain templates here, relative to this directory.
templates_path = ["html/_templates"]

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ["html/_build", "Thumbs.db", ".DS_Store", "rst/page_index.rst" ]



# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.
# See the documentation for a list of builtin themes.

html_theme = "_theme" # custom libccc_sphinx_theme
html_theme_path = ["./"]

#html_theme = "sphinx_rtd_theme"
#html_theme = "dask_sphinx_theme"
#html_theme = "asteroid_sphinx_theme"
#extensions.append("faculty_sphinx_theme")
#html_theme = "faculty-sphinx-theme"
#html_theme_options = {
#    "platform_navbar": True,
#    "platform_navbar_root": "./",
#}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_theme/other/"]
html_copy_source = False # don't include RST files in the final HTML folder

graphviz_output_format = "svg"
