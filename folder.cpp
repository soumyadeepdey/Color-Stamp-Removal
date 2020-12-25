

#include "folder.h"

using namespace IITkgp_functions;

/*-------------------------------------------------cut string upto( .)-------------------------------------------*/

/**
 * @function input_image_name_cut
 * @param : input param: input-name to be cut upto '.'
 * @return : input name upto '.'
 *
 */


char* IITkgp_functions::input_image_name_cut(const char *s)
{

                     int i;

             char *substring;

             substring = (char *)malloc(2001 * sizeof(char));

                 for(i=0; i <= strlen(s)-1; i++)
                      {

                       if (s[i]!='.' )
                substring[i] = s[i];
               else
             break;
                       }
                       substring[i] = '\0';

                     printf(" %s\n", substring);

         return(substring);



      }



/*-------------------------------------------------------------------------------------------------------------------------------------------*/



/*-------------------------------------------------MAKE DIRECTORY FUNCTION-------------------------------------------*/
/**
 * @function makedir
 * @param input a character string
 * @brief it create a directry of given character string
 */
void IITkgp_functions::makedir(char *name)
{
    int status;
    status=mkdir(name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}



/*-------------------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------------------------------------------------*/


/**
 * @function CreateNameIntoFolder
 * @param  input Foldername, desired name
 * @return : name within the desired folder
 *
 */

char* IITkgp_functions::CreateNameIntoFolder(char *foldername, char *desiredname )
{
  char *name,*output,*tempname, *tempname1;
  output = (char *) malloc ( 2001 * sizeof(char));
  if(output == NULL)
  {
    printf("Memory can not be allocated\n");
    exit(0);
  }
  strcpy(output,foldername);

  tempname = (char *) malloc ( 2001 * sizeof(char));
  if(tempname == NULL)
  {
    printf("Memory can not be allocated\n");
    exit(0);
  }
  tempname = "/";
  strcat(output,tempname);

  tempname1 = (char *) malloc ( 2001 * sizeof(char));
  if(tempname1 == NULL)
  {
    printf("Memory can not be allocated\n");
    exit(0);
  }
  strcpy(tempname1,output);

  name = (char *) malloc ( 2001 * sizeof(char));
  if(name == NULL)
  {
    printf("Memory can not be allocated\n");
    exit(0);
  }
  strcpy(name,tempname1);

  strcat(name,desiredname);

  return(name);


}


/*-------------------------------------------------------------------------------------------------------------------------------------------*/



