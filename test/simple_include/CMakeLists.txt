
add_test(NAME simple_include
    COMMAND $<TARGET_FILE:amalgamate>
        --out=${CMAKE_CURRENT_BINARY_DIR}/out.txt
        --input=${CMAKE_CURRENT_SOURCE_DIR}/group1_file1.txt,${CMAKE_CURRENT_SOURCE_DIR}/group1_file2.txt
        --filter=c:file_information,c:comment_user_include)
