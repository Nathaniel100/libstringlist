
add_executable(RefCntTest refcnt_test.c)
add_test(RefCntTest RefCntTest)

add_executable(DefTest def_test.c)
add_test(DefTest DefTest)

add_executable(StringSliceTest string_slice_test.c)
target_link_libraries(StringSliceTest stringlist)

add_executable(StringListTest string_list_test.c)
target_link_libraries(StringListTest stringlist)