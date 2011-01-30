# General build settings

# Macro for excluding files from documentation
SET(OE_DOC_EXCLUDE "")
MACRO(DOC_EXCLUDE)
  SET(OE_DOC_EXCLUDE ${OE_DOC_EXCLUDE} ${ARGV})
ENDMACRO(DOC_EXCLUDE)
