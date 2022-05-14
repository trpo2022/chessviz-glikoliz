#include "../thirdparty/ctest.h"
#include <stdio.h>


CTEST(read_txt, simple_read_file)
{
    FILE* file = fopen("test.txt", "r");
    char result[6];
    fgets(result, 6, file);
    fclose(file);

    const char expected[6] = {'a', '7', 'a', '6'};

    ASSERT_STR(result, expected);
}
