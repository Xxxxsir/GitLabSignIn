#include "defines.h"
#include <cstddef>
#include <cstdlib>
//#include <unistd.h>
#include <ctype.h>
using namespace std;
/*用户端口*/
void my_sleep(int seconds) {
    Sleep(seconds*100);
}

int Password_Text_Find(char* Password);
int Password_Text_Find1(char* Password);
int Password_Text(char* Password,int limit);
void RandID(int l, char* ch);
Account* Find_Num(char* Stu_num);

/*用户注册银行卡号*/
int SighUp()
{
    char password[7];
    Account* new_account = (Account*)malloc(sizeof(Account));
    new_account->next = NULL;
    new_account->money = 0;
    system("cls");
    printf("\n\t\t欢迎来到WHU银行注册系统！\n");
    my_sleep(1);
    printf("\t\t正在加载···\n");
    my_sleep(1);
    printf("\t\t请输入以下信息\n");
    printf("\t\t姓名：");
    setbuf(stdin, NULL);
    gets_s(new_account->name, 31);
    printf("\t\t身份证号：");
    scanf("%s", new_account->identity);
    printf("\t\t电话：");
    scanf("%s", new_account->phone);
    printf("\t\t密码：");
    Password_Input(new_account->password, 6);
    printf("\n\t\t再次输入密码：");
    if (Password_Text(new_account->password, 6) == 0) {
        printf("\n\t\t您已连续输错3次，将退出注册系统···");
        SaveRecord(4, new_account->account, NULL, 0, fail);
        my_sleep(5);
        free(new_account);
        return 0;
    }
    printf("\n\n\t\t密保问题用于找回密码\n");
    printf("\t\t如：\n");
    printf("\t\t    我的生日是？\n");
    printf("\n\t\t密保问题：");
    setbuf(stdin, NULL);
    gets_s(new_account->find_question, 31);
    printf("\t\t密保问题密码：");
    setbuf(stdin, NULL);
    gets_s(new_account->find_password, 31);

    my_sleep(1);
    printf("\n\t\t正在注册···\n");
    my_sleep(1);
    printf("\t\t···\n");
    my_sleep(1);
    printf("\t\t···\n");
    my_sleep(1);
    printf("\t\t注册成功！\n");
    RandID(12, new_account->account);
    printf("\t\t您的银行卡号是: %s\n", new_account->account);
    printf("\t\t请务必牢记银行卡号密码！\n");
    SaveRecord(4, new_account->account, NULL, 0, succ);
    printf("按任意键继续...");
    setbuf(stdin, NULL);
    getchar();
    new_account->next = account->next;
    account->next = new_account;
    return 0;
}
int ForgetPassword()
{
    Account* curacc;
    char account_tem[50];
    char password_find[7];
    system("cls");
    printf("\t\t欢迎来到找回密码系统\n");
    my_sleep(1);
    printf("\t\t正在加载···\n");
    my_sleep(1);
    int l = 1;
    while (l != 12) {
        printf("\t\t请输入银行卡号：");
        setbuf(stdin, NULL);
        cin.getline(account_tem, 50);
        if (!strcmp(account_tem, "-1"))
            return 0;
        l = strlen(account_tem);
        if (l != 12)
            printf("\t\t银行卡号有误，请输入正确长度的银行卡号\n");
    }
    account_tem[13] = '\0';
    curacc = Find_Num(account_tem);
    printf("\t\t您输入的银行卡号：");
    puts(account_tem);
    my_sleep(1);
    printf("\t\t正在为您查找\n");
    my_sleep(1);
    printf("\t\t···\n");
    my_sleep(1);
    if (curacc == NULL) {
        return 51;
    }
    printf("\t\t%s，您好！\n", curacc->name);
    my_sleep(1);
    printf("\t\t你设置的密保问题是： ");
    puts(curacc->find_question);
    putchar('\n');
    my_sleep(1);
    printf("\t\t请输入你的密保问题密码：");
    if (Password_Text_Find1(curacc->find_password) == 0) {
        SaveRecord(5, curacc->account, NULL, 0, fail);
        curacc = NULL;
        return 52;
    }
    my_sleep(1);

    printf("\t\t请输入新的密码：");
    Password_Input(curacc->password, 6);
    printf("\n\t\t再次输入密码：");
    if (Password_Text(curacc->password, 6) == 0) {
        SaveRecord(5, curacc->account, NULL, 0, fail);
        curacc = NULL;
        return 52;
    }
    printf("\n\t\t请牢记您的新密码\n");
    SaveRecord(5, curacc->account, NULL, 0, succ);
    curacc = NULL;
    printf("按任意键继续...");
    setbuf(stdin, NULL);
    getchar();
    return 0;
}
/*用户端登录*/
int SighIn()
{
    char enter_num[50];
    char enter_passw[20];
    int l = 1;
    system("cls");
    while (l != 12) {
        printf("\n\t\t请输入银行卡号：");
        setbuf(stdin, NULL);
        cin.getline(enter_num, 50);
        if (!strcmp(enter_num, "-1"))
            return 0;
        l = strlen(enter_num);
        if (l != 12)
            printf("\t\t银行卡号有误，请输入正确长度的银行卡号\n");
    }
    enter_num[13] = '\0';
    curacc = Find_Num(enter_num);
    if (curacc == NULL) {
        return 51;
    }
    printf("\t\t请输入密码：");
    if (Password_Text_Find(curacc->password) == 0) {
        SaveRecord(3, curacc->account, NULL, 0, fail);
        curacc = NULL;
        return 52;
    }
    my_sleep(1);
    printf("\n\t\t正在登录");
    my_sleep(1);
    printf("\n\t\t···\n");
    my_sleep(1);
    printf("\n\t\t登录成功！\n");
    my_sleep(1);
    SaveRecord(3, curacc->account, NULL, 0, succ);
    printf("按任意键继续...");
    setbuf(stdin, NULL);
    getchar();
    return 0;
}
