#include "Commands.h"
#include "print.h"
char usablechars[102] = {'0','1','2','3','4','5','6','7','8','9','!','"','$','%','&','/','(',')','=','?','\'','^','q','w','e','r','t','y','u','i','o','p','+','*','[',']','a','s','d','f','g','h','j','k','l','@','<','>','z','x','c','v','b','n','m',',',';','.',':','_','-',' ','\\','|','Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M','{','}','#','~'};
/*void ParseCMD(char *cmd){
    char res[sizeof(cmd)], args[sizeof(cmd)];
    //print_str(sizeof(cmd));
    /*uint8_t i = 0, fakebool = 0, cmdend = 0;;
    for(i; i < sizeof(cmd); i++){
        if(cmd[i] != " " && fakebool == 0){
            res[i] = cmd[i];
            fakebool = 1;
            cmdend++;
        }
    }
    for(i = cmdend; i < sizeof(cmd); i++){
        if(cmd[i] != '\0') args[i] = cmd[i];
    }/
    
}*/
uint8_t size(char* a){
    uint8_t i = 0;
    while(a[i] != '\0'){
        i++;
    }
    return i;
}

uint8_t search(char* test, char search){
    for(uint8_t i = 0; i < size(test); i++){
        if(test[i] == search){
            return i;
        }
    }
    return 0; //not found
}

uint8_t compare(char* a, char* b){
    uint8_t equal = 1; //true
    if(size(a) == size(b)){
        for(uint8_t i = 0; i < size(a); i++)
            if(a[i] != b[i]) equal = 0;
    } else {
        equal = 0;
    }
    return equal;
}
char cmd[100];
void resetnome(){
    size_t i;
    for(i = 0; i < 100; i++){
        name[i] = '\0';
    }
}
void resetcmd(){
    size_t i;
    for(i = 0; i < 100; i++){
        cmd[i] = '\0';
        //asm ("mov %0, 0" : "=a"(cmd[i]));
    }
}
void Run(char* command, size_t sizecmd){
    //char cmd[sizecmd];
    size_t i;
    for(i = 0; i < sizecmd; i++){
        cmd[i] = '\0';
        //asm ("mov %0, 0" : "=a"(cmd[i]));
    }
    if(search(command, (char)32) == 0) {
        for(i = 0; i< sizecmd; i++){
            cmd[i] = '\0';
            cmd[i] = command[i];
        }
    } else {
        for(i = 0; i < search(command, (char)32); i++){
            cmd[i] = command[i];
        }
    } 
    if(name[0] == '\0'){
        for(i = 0; i < sizecmd; i++){
            name[i] = cmd[i];
        }
        print_str("\nNome impostato a '");
        print_str(name);
        print_str("'\n");
        resetcmd();
        del_cursor();
        clear_row(getrow());
        print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
        print_str(name);
        print_str("@AceOS>");
        print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
        print_char(' ');
        return;
    }
    //for(i = 0; i < sizeof(usablechars); i++) if(usablechars[i] != cmd[i]) cmd[i] = ' '; 
    print_newline();
    if(compare(cmd, "print") == 1){
        if(search(command, (char)32) == 0)
            print_str("Devi mettere almeno un altro testo da printare a schermo.");
        else
            for(i = search(command, (char)32)+1; i < size(command); i++)
                print_char(command[i]);
    } else if(compare(cmd, "help") == 1 || compare(cmd, "?") == 1 || compare(cmd, "h") == 1 || compare(cmd, "\\?") == 1){
        print_str("Lista dei comandi:\n    help  - mostra la lista dei comandi - alias h, ?, \\?\n    print <arg> - funzione di print"); 
    } else {
        print_error("Non ho trovato nessun comando nominato '");
        print_error(cmd);
        print_error("'\nUsa 'help' per una lista dei comandi.");
    }
    resetcmd();
    del_cursor();
    print_char('\n');
    clear_row(getrow());
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    print_str(name);
    print_str("@AceOS>");
    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    print_char(' ');
    return;
}