
add_test(NAME simple_include
    COMMAND $<TARGET_FILE:amalgamate_all>
        --output=${CMAKE_CURRENT_BINARY_DIR}/out.txt
        --input=${CMAKE_CURRENT_SOURCE_DIR}/group1_file1.txt
        --filter=c:file_information,c:comment_user_include)
