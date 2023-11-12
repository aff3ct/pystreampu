import os
import sys

# Add source folder to path for autodoc
sys.path.insert(0, os.path.abspath("../../aff3ct"))

import sphinx_rtd_theme
# -- Project information -----------------------------------------------------

project = 'aff3ct'

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "sphinx.ext.autodoc",
    "sphinx.ext.autosummary",
    "sphinx.ext.doctest",
    "sphinx.ext.intersphinx",
    "sphinx.ext.todo",
    "sphinx.ext.coverage",
    "sphinx.ext.napoleon",
    "sphinx.ext.viewcode",
    "sphinx.ext.autosectionlabel"
    ]

# generate autosummary even if no references
autosummary_generate = True
autosummary_imported_members = True


autosectionlabel_prefix_document = True

napoleon_use_ivar = True

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

html_theme_options = {
    "collapse_navigation": False,
    "display_version": True
}

source_suffix = ".rst"

# The master toctree document.
master_doc = "index"

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

intersphinx_mapping = {'numpy': ('http://docs.scipy.org/doc/numpy/', None)}

'''
def process_docstring(app, what_, name, obj, options, lines):
    """
    Custom process to transform docstring lines Remove "Ignore" blocks

    Args:
        app (sphinx.application.Sphinx): the Sphinx application object

        what (str):
            the type of the object which the docstring belongs to (one of
            "module", "class", "exception", "function", "method", "attribute")

        name (str): the fully qualified name of the object

        obj: the object itself

        options: the options given to the directive: an object with
            attributes inherited_members, undoc_members, show_inheritance
            and noindex that are true if the flag option of same name was
            given to the auto directive

        lines (List[str]): the lines of the docstring, see above

    References:
        https://www.sphinx-doc.org/en/1.5.1/_modules/sphinx/ext/autodoc.html
        https://www.sphinx-doc.org/en/master/usage/extensions/autodoc.html
    """
    import re

    remove_directives = [
        # Remove all xdoctest directives
        re.compile(r"\s*>>>\s*#\s*x?doctest:\s*.*"),
        re.compile(r"\s*>>>\s*#\s*x?doc:\s*.*"),
    ]
    filtered_lines = [
        line for line in lines if not any(pat.match(line) for pat in remove_directives)
    ]
    # Modify the lines inplace
    lines[:] = filtered_lines

    # make sure there is a blank line at the end
    if lines and lines[-1].strip():
        lines.append("")

# Called automatically by Sphinx, making this `conf.py` an "extension".
def setup(app):
    app.connect("autodoc-process-docstring", process_docstring)
    '''