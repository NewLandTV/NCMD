/*
 * NewLand Command Prompt Poject v0.1.0 Dev
 * Developer : JkhTV
 * My own command prompt.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COMMAND_BUFFER_SIZE 4096
#define MAX_FILE_BUFFER_SIZE 2048

void Getline(char** buffer);

void Init();
void CommandProcess(char* command);

// Commands
void LoadWeb(int argc, char** argv);
void Help(int argc, char** argv);
void Clear(int argc, char** argv);
void Echo(int argc, char** argv);

int main(void)
{
	Init();
	
	char* inputBuffer;
	
	printf("\n");
	
	while (1)
	{
		printf(">");
		Getline(&inputBuffer);
		printf("\n");
		
		if (inputBuffer)
		{
			inputBuffer[strlen(inputBuffer) - 1] = '\0';
			
			CommandProcess(inputBuffer);
			free(inputBuffer);
		}
		
		printf("\n");
	}
	
	return 0;
}

void Getline(char** buffer)
{
    int c;
    char* line = malloc(MAX_COMMAND_BUFFER_SIZE);
	char* linep = line;
    size_t lenmax = MAX_COMMAND_BUFFER_SIZE;
	size_t len = lenmax;

    if (!line)
    {
    	*buffer = 0;
    	
    	return;
    }

    while (1)
	{
        c = fgetc(stdin);
        
        if (c == EOF)
        {
        	break;
		}
		
        if (--len == 0)
		{
            len = lenmax;
            
            char* linen = realloc(linep, lenmax *= 2);

            if (!linen)
			{
                free(linep);
                
                *buffer = 0;
                
                return;
            }
            
            line = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n')
        {
        	break;
        }
    }
    
    *line = '\0';
    *buffer = linep;
    
    fflush(stdin);
}

void Init()
{
	// Setup console
	system("title ncmd");
	system("mode con cols=104 lines=32");
}

void CommandProcess(char* command)
{
	int i;
	int argc;
	char* argPtr = strtok(command, " ");
	char** argv;
	
	if (argPtr)
	{
		argv = malloc(1);
		
		for (argc = 0; argPtr; argc++)
		{
			argv[argc] = malloc(strlen(argPtr) + 1);
			
			strcpy(argv[argc], argPtr);
			
			argv = realloc(argv, argc + 1);
			argPtr = strtok(0, " ");
		}
	}
	
	if (strcmpi(argv[0], "LoadWeb") == 0)
	{
		LoadWeb(argc, argv);
	}
	else if (strcmpi(argv[0], "Help") == 0)
	{
		Help(argc, argv);
	}
	else if (strcmpi(argv[0], "Clear") == 0)
	{
		Clear(argc, argv);
	}
	else if (strcmpi(argv[0], "Echo") == 0)
	{
		Echo(argc, argv);
	}
	else
	{
		printf("\'%s\' is not recognized as an internal or external command,\noperable program or batch file.", command);
	}
	
	if (argPtr)
	{
		for (i = 0; i < argc; i++)
		{
			free(argv[i]);
		}
		
		free(argv);
	}
}

// Commands
void LoadWeb(int argc, char** argv)
{
	FILE* fp = fopen(".\\web.txt", "r");
	
	if (!fp)
	{
		return;
	}
	
	char buffer[MAX_FILE_BUFFER_SIZE];
	
	while (fgets(buffer, sizeof(buffer), fp))
	{
		char* command = malloc(strlen(buffer) + 7);
		
		strcpy(command, "start ");
		strcat(command, buffer);
		printf("Loaded %s", buffer);
		system(command);
		free(command);
	}
	
	fclose(fp);
}

void Help(int argc, char** argv)
{
	printf("LoadWeb : Loads the web by taking links from the web.txt file.\n");
	printf("Help : Provides help information for Windows commands.\n");
	printf("Clear : Clears the screen.\n");
	printf("Echo : Displays messages");
}

void Clear(int argc, char** argv)
{
	system("cls");
}

void Echo(int argc, char** argv)
{
	int i;
	
	for (i = 1; i < argc; i++)
	{
		printf("%s ", argv[i]);
	}
}
