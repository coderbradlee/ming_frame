FILE(REMOVE_RECURSE
  "CMakeFiles/test_all"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/test_all.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
