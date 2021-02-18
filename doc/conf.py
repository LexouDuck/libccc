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
# sys.path.insert(0, os.path.abspath('.'))

# Specify the path to Doxyrest extensions for Sphinx:
sys.path.insert(1, os.path.abspath('doxyrest/sphinx'))



# -- Project information -----------------------------------------------------

project = 'libccc'
copyright = 'FREE'
author = 'Duquesne'

# The full version, including alpha/beta/rc tags
release = '1.0'



# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
	'doxyrest',
	'cpplexer'
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['html/_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['html/_build', 'Thumbs.db', '.DS_Store', 'rst/page_index.rst' ]



# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['doxyrest/static/']
html_copy_source = False # don't include RST files in the final HTML folder

# Specify the size of tab indentation:
doxyrest_tab_width = 4
