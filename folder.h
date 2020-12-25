
#include "StandardHeaders.h"


namespace IITkgp_functions {

  

    /**
     * @function input_image_name_cut
     * @param : input param: input-name to be cut upto '.'
     * @return : input name upto '.'
     *
     */

    char* input_image_name_cut(const char *s);

    /**
     * @function makedir
     * @param input a character string
     * @brief it create a directry of given character string
     */
    void makedir(char *name);

    /**
     * @function CreateNameIntoFolder
     * @param  input Foldername, desired name
     * @return : name within the desired folder
     *
     */

    char* CreateNameIntoFolder(char *foldername, char *desiredname );

}