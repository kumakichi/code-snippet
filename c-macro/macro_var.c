#include <stdio.h>

#define TEST(condition, ...) ((condition)?\
    printf("Passed test:%s\n", #condition):\
    printf(__VA_ARGS__))

#define PRINT_INT(n) (printf(#n "=%d\n", n))	/* # 串化 */
#define MK_ID(n) san##n		/* ## 连接 */

#define TO_STRING(x) TO_STRING1(x)
#define TO_STRING1(x) #x

int main(void)
{
	int MK_ID(1), MK_ID(ye), MK_ID();	/* 最后一个因为没填，所以扩展为""，所以直接就是san */

	printf("%s\n", TO_STRING(MK_ID(1)));
	printf("%s\n", TO_STRING(MK_ID(ye)));

	san = 78;
	san1 = 1;
	sanye = 2;

	PRINT_INT(san1);
	PRINT_INT(sanye);

	TEST(san1 <= sanye, "%d is bigger than %d\n", san1, sanye);
	TEST(sanye <= san1, "%d is bigger than %d\n", san1, sanye);

	return 0;
}
