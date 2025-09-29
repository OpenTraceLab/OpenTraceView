# Manual documentation build
# This is a simplified version - the original CMake version has complex
# asciidoctor processing which can be added later if needed

manual_sources = files(
  'manual.txt',
  'overview.txt',
  'installation.txt',
  'acquisition.txt',
  'analysis.txt',
  'decoders.txt',
  'import_export.txt',
  'cli.txt',
  'license.txt'
)

# For now, just install the text files
# TODO: Add asciidoctor processing if needed
install_data(manual_sources,
  install_dir: get_option('datadir') / 'doc' / 'opentraceview'
)
