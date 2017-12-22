#include <stdio.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matche(char *pline, char *pattern) {
	if(pline[0] != '\0'){
		if(pattern[0] != '\0'){

			if(pattern[0] == '\\' && pattern[1] != '+' && pattern[1] != '.'){
			if( pattern[1] == '?'){
       // pattern[1] == '.' || pattern[1]== '+'||
					int h =0;
					int count =0;
					while(pattern[1] == '?' && pline[h] != '\0'){
						if(pline[h] == '?')
							count ++;
						h++;
					if(count < 1)
						return 0;
					}
                    return matche(pline+1,pattern+2);
				}

				return matche(pline, pattern+1);
			}

            else if(pattern[1]=='+'){ // checking char
				int i=0;
				int j=0;
				if(pattern[0] == '\\' && pattern[-1] != '\\'){
					while(pline[0] == '\\'){
						pline++;
						if(pline[0] == '\0')
							return 0;
					}
					return matche(pline,pattern+1);
				}
				if(pattern[0] == '.'){
					if(pattern[2]=='\0')
						return 1;
					while(pline[j] != pattern[2]){
						j++;
						if(pline[j] == '\0')
							return 0;
					}

					return matche(pline+j,pattern+2);

				}
				while(pline[i] == pattern[0]){
					i++;
				}
				if(i > 0){
					pattern = pattern +2;
					return matche(pline+i, pattern);
				}
				else
					return 0;
			}


			else if(pattern[0] == '?'){
				return matche(pline, pattern -1);
			}

			else if(pattern[1] == '?'){ // checking char

				if(pattern[0] == '.'  && pattern[0] != '\\'){
					if(matche(pline, pattern+2))
						return 1;
					else if(matche(pline+1, pattern+2))
						return 1;
					else
						return 0;
				}

                else if(pline[0] == pattern[2]){
					if(matche(pline, pattern+2))
                        return 1;
				}
				 else if(pline[0] == pattern[0]){
					return matche(pline+1, pattern+2);
				}
				else if(pattern[0] == pattern[2]){
					pattern = pattern +2;
					return matche(pline, pattern);
				}

				else if(pattern[0] != pline[0])
					return 0;

			}


			else if(pattern[0] == '.'){
				if(pattern[0] == '\\')
					return 0;
				return matche(pline+1, pattern+1);
			}

			else if(pline[0] == pattern [0])
				return matche(pline+1, pattern+1);
			else
				return 0;
		}
		return 1;
	}
  return 0;
}





/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
	int i=0;
	while(line[i]!='\0'){
		if(matche(line+i, pattern))
			return 1;
		i++;
	}

	if(pattern[0]=='\0')
		return 1;


    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
