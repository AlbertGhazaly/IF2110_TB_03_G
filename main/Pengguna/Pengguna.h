#include "../../modules/adt.h"

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_BIO_LENGTH 135
#define MAX_HP_LENGTH 100
#define MAX_WETON_LENGTH 50
#define MAX_JENIS_LENGTH 50
#define MARKACC '\0'

typedef struct {
    Word username[MAX_USERNAME_LENGTH];
    Word password[MAX_PASSWORD_LENGTH];
    Word bio[MAX_BIO_LENGTH];
    Word noHP[MAX_HP_LENGTH];
    Word weton[MAX_WETON_LENGTH];
    Word jenisAkun[MAX_JENIS_LENGTH];
} Account;

#define Username(U) (U).username
#define Password(U) (U).password
#define Bio(U) (U).bio
#define NoHP(U) (U).noHP
#define Weton(U) (U).weton
#define JenisAkun(U) (U).jenisAkun


#define MAX_ACCOUNTS 20
typedef struct {
    Account accounts[MAX_ACCOUNTS];
    int count;
} AccountList;

void inUser(Word *array, Word username);

void outUser(Word *array);

boolean isOnline(Word *array);

void CreateAccount(Account *account, Word username, Word password);

void signup(AccountList *listakun);

void fillAccount(AccountList *listakun);

void CreateAccountEmpty(Account *account);

void CreateAccountList(AccountList *list);

void AddAccountToList(AccountList *list, Account account);

void DisplayAccounts(AccountList *list);

boolean IsAccountListFull(AccountList *list);

boolean WordEqualAccount(Word a, Word b);

boolean IsEqualUsername(Word *word1, Word *word2);

boolean IsUsernameInAccountList(AccountList *list, Word username);

boolean cekPassword(AccountList *list, Word username, Word password);

void ReadUser_FILE(char filename[], AccountList *list, Matrix *teman);

void edit_account(AccountList *list, Word user);