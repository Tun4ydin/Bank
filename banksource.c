
//Mock-up bank application by Tuna AYDIN
//Openssl doesn't work figure out why(For cxx: there is incompatibility. For clion: I didnt downloaded it.)
//19/12/2024
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

struct login
{
    char username[30];
    char password[65];
    long long int initial;
};

// Prototypes
void logs();
void registration();
void money(struct login user);
// Prototypes

// MAINBOI
int main()
{
    char cho;
    printf("Press 1 for logging in, press 2 for registering (Pressing any other button will close the program): ");
    scanf(" %c", &cho);
    switch (cho)
    {
        case '1':
            logs();
            break;
        case '2':
            registration();
            break;
        default:
            printf("Goodbye. Have a good day.");
            return 3;
    }
    return 0;
}
// MAINBOI

// Money Calc
void money(struct login user)
{
    FILE *file;
    int app;
    long long int extra;
    char dec;
    int terminator = 1;

    do
    {
        printf("Your current balance is: %lld\n", user.initial);
        printf("Press 1 to withdraw money, 2 to deposit money, 3 to exit: ");
        scanf("%d", &app);

        switch (app)
        {
            case 1: // Withdrawal from account
                do
                {
                    printf("Enter amount to withdraw: ");
                    scanf("%lld", &extra);

                    if (extra > user.initial || extra <= 0)
                        printf("Invalid input. Please try again.\n");

                } while (extra > user.initial || extra <= 0);

                printf("Are you sure? Press N to cancel, any other key to confirm: ");
                scanf(" %c", &dec);

                if (dec == 'N')
                {
                    break;
                }
                system("cls");
                   for(int i = 0;  i < 3; i++)
                  {
                      printf("Processing.");
                      sleep(1);
                      printf(".");
                      sleep(1);
                      printf(".");
                      sleep(1);
                      system("cls"); 
                }

                user.initial -= extra;
                printf("You have withdrawn %lld. New balance: %lld\n", extra, user.initial);
                break;

            case 2: // Deposit the money
                do
                {
                    printf("Enter amount to deposit: ");
                    scanf("%lld", &extra);

                    if (extra <= 0)
                        printf("Invalid input. Please try again.\n");

                } while (extra <= 0);

                printf("Are you sure? Press N to cancel, any other key to confirm: ");
                scanf(" %c", &dec);

                if (dec == 'N')
                {
                  break;
                }

                system("cls");

                   for(int i = 0;  i < 3; i++)
                  {
                      printf("Processing.");
                      sleep(1);
                      printf(".");
                      sleep(1);
                      printf(".");
                      sleep(1);
                      system("cls");
                  }

                user.initial += extra;
                printf("You have deposited %lld. New balance: %lld\n", extra, user.initial);
                break;

            case 3: // Exit the program
                terminator = 0;
                system("cls");
                printf("Goodbye. Have a good day.\n");
                break;

            default:
                printf("Invalid input. Please try again.\n");
        }

        // Update the balance in the file
        file = fopen("registry.txt", "r+");//
        if (file == NULL)
        {
            perror("Error opening file");
            exit(1);
        }

        struct login temp;

        while (fread(&temp, sizeof(temp), 1, file))
        {
            if (strcmp(temp.username, user.username) == 0)
             {
                fseek(file, -(long int)sizeof(temp), SEEK_CUR);//
                fwrite(&user, sizeof(user), 1, file);
                break;
            }
        }

        fclose(file);

    } while (terminator == 1);
}

void HashPassword(const char *password, char *blabber)
 {
    unsigned long long hash = 0;
    for (int i = 0; password[i] != '\0'; i++)
     {
        hash = hash ^ ((unsigned long long)password[i] << (i % 4));//
    }
    sprintf(blabber, "%llx", hash);
}


// Registration Function
void registration(void)
{
    FILE *log;

    log = fopen("registry.txt", "a");
    if (log == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    struct login newUser;
    char placeholderpass[30];

    printf("Enter Username: ");
    scanf("%s", newUser.username);
    printf("Enter Password: ");
    scanf("%s", placeholderpass);
    printf("Enter initial amount of money: ");
    scanf("%lld", &newUser.initial);

    HashPassword(placeholderpass, newUser.password);

    fwrite(&newUser, sizeof(newUser), 1, log);

    fclose(log);

    printf("Registration Successful.");
    system("cls");
    logs();
}

// Login Function
void logs(void)
{
    FILE *log;
    char username[30], placeholderpass[30], blabberpass[65];
    struct login user;

    log = fopen("registry.txt", "r");
    if (log == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", placeholderpass);

    HashPassword(placeholderpass, blabberpass);

    int found = 0;
    while (fread(&user, sizeof(user), 1, log))
    {
        if (strcmp(username, user.username) == 0 && strcmp(blabberpass, user.password) == 0)
        {
            found = 1;
            printf("Login successful!\n");
            fclose(log);
            system("cls");
            money(user);
            return;
        }
    }

    fclose(log);
    if (!found)
    {
        printf("Invalid login information. Please try again.\n");
    }
}