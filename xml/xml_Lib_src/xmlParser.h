
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Program Name : xmlParser.h
// 
// Project :  		Video Object Analysis
// Author : 		Gaurav Harit (PhD EE-2001)
// Creation Date : 	Sep 17  -2005.  Rights Reserved
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*


#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <vector>
#include <stack>
#include <queue>
#include <iomanip>
#include <ostream>

using namespace std;
#ifndef	_XMLPARSER
#define	_XMLPARSER

class	XMLparser; 
class	SchemaDynamicStructures; 
class	XSDNestedStructure;
class	XSDparser;
class	XSDLeaf;
class	XSDType;
class	XSDElementGroup;
class	XSDElementDefinition;
class	XSDAttributeGroup;
class	XSDAttributeDefinition;
class	XSDRestriction; 
class	XSDAllowedElement; 
class	XSDSimpleDataType;
//class	NestingInfo;
class	IncompleteWork;

class	XMLattribute {
	public:
				char	*name;
				char	*value;
															 XMLattribute ();
															~XMLattribute ();		
					void	print();										
					void	setName  (char *n);
					void	setValue (char *v);
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



class	XMLelement {
	public:
	char					*name, *content;
	vector<XMLelement*>		childs;
	XMLelement				*parent; 
	vector<XMLattribute*>	attributes;
	long int				filePointer;
	
	vector<char*>			counterNames; // For children
	vector<int>				counters;
	int						childCounter, myID;
	
								 				 XMLelement();
												~XMLelement ();		
			void 	print (int detail=0);
			void	setName (char *n);
			void	setContent (vector<char *>	& contentArray);
			void		setContent (char *unitChars, int uc);
			void		setContent (char *myString);
			char*	getAttributeValue (char *name);
			bool 	getAttributeValue (char *name, float & value);
			bool 	getAttributeValue (char *name, int & value);
			bool 	hasAttributeValue (char *name, char *value); 

			XMLattribute* 	getAttributeByValue (char *value);
			XMLattribute* 	getAttribute (int count);
				
			XMLelement* 	getChild (char *name=NULL);
			XMLelement* 	getNextChild (char *name=NULL);
				
			XMLelement* 	getChild (int num);	
			XMLelement* 	getChild (char *name, int num);
			
			XMLelement* 	getSibling (int count); 




			int 	assignAttributes (vector<char*> &  bufferedNames);
			void	readFullElement (XMLparser *parser);
			void	freeUp();
			void	reset (bool alsoChildren=true);
			void	dumpInFile (XMLparser *parser, char *indent, int level);
			
			XMLelement*	makeChildElement (char *name);	
			void		addChildElement (XMLelement *child);
			void		setAttribute (char *name, char *value);
			void 		addContent (char*  givenString);
			
			void 		setChildElement (XMLelement	*bel);
			
			void 		tokenizeLineWise (char *contArray, vector<char*> & lineWords, 
										vector<int> & nWordsEachLine, bool alsoPrint=false);
			char * 		cloneString (char *n);
			
			void 		printAttributes (); 

};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
	
	

class	XMLparser {
	
	public:
		vector<char*>			tokens;	
		vector<int>				lineNumbers;
		vector<XMLelement*>		elementList;
		queue<XMLelement*>		poolElements;
		queue<XMLelement*>		usedElements;
		
		vector<char*> 		lineWords;
		vector<int>			nWordsEachLine;

		char						*fileName;
		fstream						fin, fout;
		char						*firstWord, *textLine, *unitChars; int MAXCHARS;
		XSDparser					*xsdParser; 				
		long int					pCurrentPos;
		
				XMLparser ();
		bool	readXMLdocument (char *fileName);
		bool	readXMLdocument_old (char *fileName);
		void 	readDocument (char *fileName);
	
	
		void 	makeXMLgraphicalStructure (vector<char*>	& tokens);
		void	reset ();
		char * 	makeString (vector<char> & unitChars);	 

		char * 	makeString (char* & unitChars, int & uc);
		bool 	shortHandReadRootElements (char *fileName);
		void	dumpInFile (char *fileName);	
		void	writeComment (char *buf);
		
		XMLelement*	makeXMLelement(char *name);
		void		test();
		void		print();
		void 		setOutputFile (char *fileName);
		void 		tokenizeLineWise (char *contArray, vector<vector<char*> > & lines);
		char * 		cloneString (char *n);
		void 		tokenizeLineWise (char *contArray, vector<char*> & lineWords, 
										vector<int> & nWordsEachLine, bool alsoPrint=false);
		XMLelement*	getElementFromPool ();
		void		fillBackElementPool ();	
		bool 		assertFullBuffer (char *textBuf, int & cIndex, int & requestedBytes, 
										int _bufSize, int lookAhead, int totalFileSize);
		
		bool		checkXMLcomment  (char *dataBuf, int & k, int & requestedBytes, 
										bool & xmlComment, int _bufSize, int totalFileSize);
							
		void 		makeListOfMatchingElements (	char 				*requestedElementName, 
													char				*nameOfElementToAvoid,
												XMLelement 				*gElem, 
												vector<XMLelement*> &  	filteredList);  
		bool 		matchesToken (char *dataBuf, char *gToken); 
		void 		ifNecessaryReallocate (char *& unitChar, int uc, int & MAXCHARS); 

		void		verifyAgainstSchema (vector<XMLelement*> & elementList, 
										 vector<XMLelement*> & schemaElementList);  
																	
		void		verifyAgainstSchema (char *schemaFileName, int debug=0); 
	
		int 		calculateLineNumber (fstream &fin, int k, int m);
		void 		flagError (stack<XMLelement*> & rElStack, char *dataBuf, int req, int bufferReadUpto,
																					char *gToken, int msgCode);  
		
		bool
					searchElement (char *requiredElementName, 	XMLelement				*gElem,
																vector<char*> 			& requiredAttrVals, 
															 	vector<XMLelement*>		& matchingElementsV,
																bool 		 			toCheckRecursive); 
		bool 		searchKeyword (char *keyword,	XMLelement				*gElem,
													vector<int>				& matchesWithWhat, 
													vector<XMLelement*>		& matchingElementsV,
													bool 					toCheckRecursive); 

		bool 		matchesElementNameOnly (char *eName, char *eNameWithoutNamespace); 
	
		/*
		void 		flagSchemaError (int errorCode=0, char *msg=NULL); 
		void 		prepareSchemaSearchOrder (vector<int> & parentSchemaPath, int Z, vector<int> & schemaSearchOrder); 
	*/												
	
	//	void 		getTracePathForElement (XMLelement *eleMc, XMLelement *sElem, NestingInfo *& myInfo);	
																	
	

};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

/*
class 	NestingInfo {
		public:
						NestingInfo			*parent;
						XMLelement			*elem;
						int					myNumber;
						vector<int>			pathFromRoot;
																			~NestingInfo();
																			 NestingInfo();
				void	print(); 
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
*/ 


class	SchemaDynamicStructures {
		public:					
				XSDElementDefinition		*xsdElem;
				XMLelement					*eleM; 
				XMLattribute				*attr;
				XSDAttributeDefinition		*xsdAttr;
				XSDType						*xType; 
				XSDLeaf						*xLeaf;
				char						*fileNameInWhichErrorOccurred;
				vector<IncompleteWork*>		incompleteWorksV;
		/*
					vector<XMLelement*>		xxSchemaElementsV;
					vector<char*>			requiredAttrValues;
																		
					XMLelement				*eleM, *schel, *eleMc;
						int					startI, endI; 
				queue<XMLelement*>			elmQueue;
				vector<XMLelement*>			matchingElementsV;
									
				vector<int>	 				startIndexA, endIndexA, schemaPathStore,
											parentSchemaPath, schemaSearchOrder;	
												
				vector<XMLelement*>			virtualElemA, virtualSchElemA;
		*/	
					
			
																				 SchemaDynamicStructures();	
																				~SchemaDynamicStructures();	
				void 	reset(); 																
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



class	XSDparser {
	public:	
	//vector<SchemaDictatedInformation*>		sInformationV;
						char*				schemaFileName; 
				//vector<XMLelement*>			schemaElementList; 
						vector<char*>		xsdSimpleDataTypesV; //, schemaTokens;			
			vector<XSDAllowedElement*>		xsdAllowedElementsV;
	//					vector<int>			stid, dtid;
	//				    		int			nSTokens, nDTokens; 
			vector<XSDElementDefinition*>		xsdElementDefsV;
			vector<XSDAttributeDefinition*>		xsdAttributeDefsV;			
			vector<XSDElementGroup*>			xsdElementGroupsV;
			vector<XSDAttributeGroup*>			xsdAttributeGroupsV; 
			vector<XSDType*>					xsdTypesV; 
			XSDSimpleDataType					*xsdSimpleDataType; 
			SchemaDynamicStructures				*sdd;
						char					*buf; 															
						XMLparser				*xmlParser; //For reading the schema file 
						int						debug;
																			~XSDparser();			
																			 XSDparser();			
				void	print(); 				
				void	reset(); 
				void 	checkSchemaStructure (XMLelement *sElement); 
				int		getSchemaTokenIndex (char *tokName); 
				void	extractSchemaDictatedInformation (vector<XMLelement*> & sElements, XMLparser*); 	
				bool 	matchesElementNameOnly (char *eName, char *onlyName);   
				
				void	setString(char *& tString, char * gString);
				void	popError(int eCode, char *gValue=NULL); 
				
				XSDElementDefinition* 		attemptToMakeXSDElementDefn (XMLelement *elem);
				XSDAttributeDefinition* 	attemptToMakeXSDAttributeDefn (XMLelement *elem); 
							XSDType* 		attemptToMakeXSDType (XMLelement *elem); 
					XSDRestriction* 		attemptToMakeXSDRestriction (XMLelement *elem);
				XSDNestedStructure* 		attemptToMakeXSDNestedSt (XMLelement *elem);  
	
					XSDElementGroup* 		attemptToMakeXSDElementGroup (XMLelement *elem); 
				  XSDAttributeGroup* 		attemptToMakeXSDAttributeGroup (XMLelement *elem);
	
						void 		fillUpDetailsForXSDType (XSDType *xType, XMLelement *elem); 
						void 		verifyElementWithSchemaSpecs (XMLelement *xElem, 
																  XSDElementDefinition *xsdElemg=NULL); 
		XSDElementDefinition* 		getXSDElementDefinition (char *gElemName, XSDElementDefinition *withinElem=NULL); 
		XSDAttributeDefinition* 	getXSDAttributeDefinition (char *gName, XSDType *withinType=NULL); 
						XSDType* 	getXSDType (char *gTypeName); 
						void 		removeNameSpaceQualifier (char *eName);  
			XSDAttributeGroup* 		getXSDAttributeGroup (char *gName); 
				XSDElementGroup* 	getXSDElementGroup (char *gName);  
	
						int 		calculateLineNumber (char *fileName, long int filePointer);   
	
						void 		extendXSDType (XSDType *newerType, XSDType *olderType); 
	
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_





class	XSDElementDefinition {
	public:		
						char				*name,
											*xTypeName;
						XSDType				*xType;
						bool				isReference; 
																				~XSDElementDefinition();
																				 XSDElementDefinition();
						void	print(char *indent=NULL);
						void	setString(char *& tString, char *gString);
						bool 	checkOtherPossibleAttributes (char *attrName);  
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



class	XSDAttributeDefinition {
	public:
				char		*name, *fixed;
				XSDType		*xType;
				bool		isReference; 
																				~XSDAttributeDefinition();	
																				 XSDAttributeDefinition();	
				void	print (char *indent=NULL);
				bool 	verifyValue (char *gValue, XSDparser *xsdParser); 
				
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!

class	XSDType	{
	public:						
						char								*name;
						XSDType								*extensionOf;
						XSDRestriction						*xRestriction; 
						XSDNestedStructure					*nst;
						vector<XSDAttributeDefinition*>		attributesV;
						vector<XSDAttributeGroup*>			attrGroupsV;
						bool								isReference; 
																				~XSDType();
																				 XSDType();
						void	print(char *indent=NULL);
						void	setString(char *& tString, char *gString);
						bool 	verifyValue(char *gValue, int msgCode, XSDparser *xsdParser, bool dontExit=false); 	

};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!





//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 	Should handle enumeration, (for base=string)
// 						minInclusive, maxInclusive (for base=integer)
// 						xs:pattern (for base=string)
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
class	XSDRestriction {
	public:
				char				*base;
				vector<char*>		enumeration;
				float				minInclusive, maxInclusive; 
				int					howSpecified;   
																				~XSDRestriction();
																				 XSDRestriction();
			void	print (char *indent=NULL); 		
			bool 	verifyValue (char *gValue, int msgCode, XSDparser *xsdParser, bool dontExit=false); 

			
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



class	XSDElementGroup {
	public:	
					char				*name;
					bool				isReference;
	vector<XSDElementDefinition*>		grpElementsV; //Not sure whether a group can have further groups
																				~XSDElementGroup();
																				 XSDElementGroup();
							void		print(char *indent=NULL); 			
							bool 		isGroupMember (char *gElemName); 
			XSDElementDefinition* 		getGroupMember (char *gElemName);  
		
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


class	XSDAttributeGroup {
	public:
					char				*name; 
					bool				isReference; 
	vector<XSDAttributeDefinition*>		grpAttributesV;
																				~XSDAttributeGroup();	
																				 XSDAttributeGroup();	
							void		print(char *indent=NULL); 																	 
							bool 		isGroupMember (char *gElemName); 
			XSDAttributeDefinition* 	getGroupMember (char *gElemName);  
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!





//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
class	XSDNestedStructure {
	public:
				vector<XSDLeaf*>			xLeafV;
				//XSDDecomposition			*xDecomposition; 
				vector<int>					cardinalityStatus, min, max;
				bool						isUnion, isSequence, isAnyOrder; 	

																				~XSDNestedStructure();
																		 		 XSDNestedStructure();
				void	print(char *indent=NULL);
				bool	examineAttributeValue (char *value); 
				void 	addToNestedStructure (XSDNestedStructure *givenNstStructure); 

};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


class	XSDLeaf {
	public:
				XSDElementDefinition		*xElem;
				XSDElementGroup				*xElemGrp;
				XSDAttributeDefinition		*xAttr;
				XSDAttributeGroup			*xAttrGrp;
				XSDType						*xType; 
				XMLelement					*oElem; 
																				~XSDLeaf();
																				 XSDLeaf();
				void	print(char *indent=NULL);
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


/*
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
class	XSDDecomposition {
	public:
				vector<XSDNestedStructure*>	childTags;
				vector<int>					cardinalityStatus, min, max;
				bool						isUnion, isSequence, isAnyOrder; 	
																			   ~XSDDecomposition();
																		 		XSDDecomposition();
				void 	print();																
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

*/



//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
class	XSDAllowedElement {
			public:
									char		*name;
					vector<XSDAllowedElement*>	allowedChilds;
								vector<char*>	allowedChildsN;	// Names of the allowed children  
								vector<char*>	allowedAttrs, allowedNameSpaces;
									int			myID;
																		~XSDAllowedElement();			
																		 XSDAllowedElement();			
				void 	print(char *indent=NULL);
				void	setName(char *n);
				void 	addChildName(char *n);
				void 	addAttributeName(char *n); 
				bool	matchesElemName (char *n);
				void 	checkSchemaElementStructure (XMLelement *sElement, XSDparser *spc, int debug=0); 

};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
class	XSDSimpleDataType {
			public:
																		~XSDSimpleDataType();			
																		 XSDSimpleDataType();			
				void 	print(char *indent=NULL);
				bool	checkSimpleDataType (char *dataType, char *value, XSDparser *xsdParser=NULL); 
				int 	isItTextOrNumber (char *gValue); 
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
class IncompleteWork {
	public:
				char 		*workName;
				XSDType		*xType;
				XMLelement	*xelem;
											 IncompleteWork(XMLelement *xelem, XSDType *xType, char *workName);
											 IncompleteWork();
											~IncompleteWork();
				void print(); 							
};//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



#endif



