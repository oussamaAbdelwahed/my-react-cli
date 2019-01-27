#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include<ctype.h>

#define false 0
#define true 1
typedef int boolean;

#define STATELESS_OPTION "-sl"
#define STATEFUL_OPTION "-sf"

char * getStatelessComponentArrowFunctionName(char fileName[]){
	fileName[0]=tolower(fileName[0]);
	return fileName;
}

void createStatelessComponentBaseCode(char fullPath[],char fileName[],boolean withCss) {
    char*  jsFile = (char*)malloc(strlen(fullPath) * sizeof(char));
    strcpy(jsFile,fullPath);
    strcat(jsFile,".js");
   FILE * jsf = fopen(jsFile,"w");
   if(jsf!=NULL){
   	   fprintf(jsf,"import React from \"react\";\n");
   	   if(withCss==true){
   	   	  fprintf(jsf, "import classes from \"./%s.%s\";\n",fileName,"css");
		  char * cssFile = (char*)malloc(strlen(fullPath) * sizeof(char));
		  strcpy(cssFile,fullPath);
		  strcat(cssFile,".css");
		  FILE * cssFileObj = fopen(cssFile,"w");
		  fclose(cssFileObj);
		  free(cssFile);
       }
       char * arrowFunctionName = getStatelessComponentArrowFunctionName(fileName);
   	   fprintf(jsf,"const %s = (props) => {\n\n",arrowFunctionName);
   	   fprintf(jsf, "\t return <></>;\n");
   	   fprintf(jsf, "};\n\n");
   	   fprintf(jsf, "export default %s;",arrowFunctionName);
   }
   fclose(jsf);
   free(jsFile);
}

void createStatefulComponentBaseCode(char fullPath[],char fileName[],boolean withCss){
	 char*  jsFile = (char*)malloc(strlen(fullPath) * sizeof(char));
     strcpy(jsFile,fullPath);
     strcat(jsFile,".js");
     FILE * jsf = fopen(jsFile,"w");
	 if(jsf!=NULL){
	 	 fprintf(jsf, "import React, {Component} from \"react\";\n");
	 	 if(withCss==true){
	 	 	fprintf(jsf, "import classes from \"./%s.%s\";\n",fileName,"css");
			char *  cssFile = (char*)malloc(strlen(fullPath) * sizeof(char));
			strcpy(cssFile,fullPath);
			strcat(cssFile,".css");
			FILE * cssFileObj = fopen(cssFile,"w");
			fclose(cssFileObj);
			free(cssFile);
        }
	    fprintf(jsf, "class %s extends Component {\n",fileName);
	    fprintf(jsf, "\trender(){\n");
	    fprintf(jsf, "\t\treturn <></>;\n");
	    fprintf(jsf, "\t}\n");
	    fprintf(jsf, "}\n\n");
	    fprintf(jsf, "export default %s;",fileName);
	 }
	 fclose(jsf);
	 free(jsFile);
}


int main(int argc,char * argv[]) {
	if(argc >=3){
		char buff[FILENAME_MAX];
		char * currentBaseDir = _getcwd(buff,FILENAME_MAX);
		char * command = argv[1];
		if(strcmp(command,"g")==0 || strcmp(command,"generate")==0){
			char * fileNameWithPath = argv[2];
		    if(fileNameWithPath!=NULL) {
		       char  truePath[100]= {NULL};
		       char * token= strtok(fileNameWithPath,"/");
		       char * theFileName=fileNameWithPath;
		       while(token!=NULL){
		       	strcat(truePath,"\\");
		       	strcat(truePath,token);
		       	theFileName = token;
		       	token = strtok(NULL,"/");
		       }
		       char theFileNameWithExtension[50] = {NULL};
		       strcat(theFileNameWithExtension,theFileName);
		       strcat(theFileNameWithExtension,".js");
		       
		       /*strcat(truePath,".js");
		       strcat(truePath,"\0");*/

		       char fullAbsolutePathWithName[150]={NULL};

		       strcat(fullAbsolutePathWithName,currentBaseDir);
		       strcat(fullAbsolutePathWithName,truePath);
		       strcat(fullAbsolutePathWithName,"\0");
		       if(argc>4 && (strcmp(argv[3],STATEFUL_OPTION)==0 || strcmp(argv[4],STATEFUL_OPTION)==0 || strcmp(argv[3],STATELESS_OPTION)==0 || strcmp(argv[4],STATELESS_OPTION)==0)){
		       	   if(strcmp(argv[3],STATEFUL_OPTION)==0 || strcmp(argv[4],STATEFUL_OPTION)==0){
		       	   	   if(strcmp(argv[3],"-css")==0 || strcmp(argv[4],"-css")==0){
                          createStatefulComponentBaseCode(fullAbsolutePathWithName,theFileName,true);
		       	   	   }else{
                       	  createStatefulComponentBaseCode(fullAbsolutePathWithName,theFileName,false);
		       	   	   }
		       	   }else{
		       	   	  if(strcmp(argv[3],"-css")==0 || strcmp(argv[4],"-css")==0){
                        createStatelessComponentBaseCode(fullAbsolutePathWithName,theFileName,true);
                      } else{
                        createStatelessComponentBaseCode(fullAbsolutePathWithName,theFileName,false);
                      }
		       	   }
		       }else{
		       	   if(strcmp(argv[2],"-css")==0 || (argv[3]!=NULL && strcmp(argv[3],"-css")==0)){
		              createStatelessComponentBaseCode(fullAbsolutePathWithName,theFileName,true);
		       	   }else{
		              createStatelessComponentBaseCode(fullAbsolutePathWithName,theFileName,false);
		           }
		       }
		    }
		}
   }
   return 1;
}