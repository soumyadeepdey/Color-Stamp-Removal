/**************************************************//**
 * \file xml.h
 * \author Ritu Garg
 * \dated 03-03-2010
 * \brief Defines the routines for parsing, writing and updating XML file using the xmlParser Library.  
 *****************************************************/
 /**
  * \author Soumyadeep Dey
  * \modified date 03-03-12
  * 
  */
#ifndef _XML
#define _XML
 
#include "xml_Lib_src/xmlParser.h"

namespace IITKGP_XML_IO
{
/**	\class XML_IO
*	\brief class contains all variables and function for reading and creating XML file
*/

class XML_IO
{
	public:
/**			\fn char* readXML(char *XMLFile)
 *			\brief Parses the input XML file structure and reads the input document page to be processed. 
 *			\param char *XMLFile stores the name of the input XML file
 *			\return input document pag to be processed.
 */
		char* readXML(char *XMLFile);
		
/**			\fn void WriteOutXML(char *inputXMLfile, char *outXML, char *tx_in_page, char *tx_out_page,
	   			 char *gr_in_page, char *gr_out_page, int graphFlag, vector<int>& blk_Label, 
				 vector<int>& x1,vector<int>& x2,vector<int>& y1, vector<int>& y2)
 *			\brief write the intemediate as well as final output of segmentation and classification into XML file
 *			\param char *inputXMLfile stores the input XML file
 *			\param char *outXML stores the output XML file name
 *			\param char *tx_in_page stores the name of the input page fpr text extraction
 *			\param char *tx_out_page stores the name of the final output after all the text has been extracted.
 *			\param char *gr_in_page stores the name of the page given as input for graphics recognition
 *			\param char *gr_out_page storesthe name of fial output of the graphics extracted from the input page
 *			\param int graphFlag indicates the presence of graphics blocks in the input page
 *			\param vector<int>& blk_Label stores the information as to which block is a text block or a graphics block
 *			\param vector<int>& x1,vector<int>& x2,vector<int>& y1, vector<int>& y2 store the top left and bottom right coordinates of the blocks generated after segmentation.
 *			\return none
 */
		void WriteOutXML(char *inputXMLfile, char *outXML, char *tx_in_page, char *tx_out_page,
	   			 char *gr_in_page, char *gr_out_page, int graphFlag, vector<int>& blk_Label, 
				 vector<int>& x1,vector<int>& x2,vector<int>& y1, vector<int>& y2);
/**			\var char *page
 *			\brief stores the input image name
*/
		char *page;

/**			\var int cropFlag
 *			\brief indicates whether COPPING tag exists inthe input XML file
*/
		int cropFlag;

/**			\var vector <int> leftX,leftY,rightX,rightY
 *			\brief stores top left and bottom right coordinates of the blocks obtained after segmentation
*/
		vector <int> leftX,leftY,rightX,rightY;
		
/**			 \fn void writemyxml(char *inputXML ,char *outputxml, char *input_image, char *output_image)
 * 			 \brief write the outputxml of marginal moise remove
 * 			 \param char *inputXML stores the input XML file
 * 			 \param char *outputxml stores the output XML file name
 *			 \param char *childtype give the type of child
 * 			 \param char *input_image stores the input image name
 * 			 \param char *output_image stores the output image name
 * 			 \param char *angel skew angel
 * 			 \param char *algorithmname name of the algorithm used for skew correction 
 * 			 \param int  toplx is the top-most left, x co-ordinate of the detected page frame
 * 			 \param int  toply is the top-most left, y co-ordinate of the detected page frame
 * 			 \param int  btmrx is the bottom-most right x-co-ordinate of the detected page frame
 * 			 \param int  btmry is the bottom-most right y-co-ordinate of the detected page frame
 * 
 */
		void writemyxml(char *inputXML ,char *outputxml, char *childtype,char *input_image, char *output_image,
				char *angel, char *algorithmname, int toplx, int toply, int btmrx, int btmry);

		XML_IO();///<the constructor.
		~XML_IO();///<the desttructor.
};
}
#endif
