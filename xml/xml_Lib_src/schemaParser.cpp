
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Program Name :  	schemaParser.cpp
// 
//
// Project :  		OCR
// Author : 		Gaurav Harit (PhD EE-2001)
// Creation Date : 	April 10 -2007.  Rights Reserved
// 					This is a cleaner version of an original program
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*

#include	"xmlParser.h"



XSDElementDefinition::~XSDElementDefinition() {}
XSDElementDefinition::XSDElementDefinition() {
			name = NULL; xTypeName = NULL; xType = NULL; isReference = false;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



XSDAttributeDefinition::~XSDAttributeDefinition() {}
XSDAttributeDefinition::XSDAttributeDefinition() {
			name = NULL; isReference = false; fixed = NULL; xType = NULL; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!

void
XSDAttributeDefinition::print(char *indent) {
																			char *myIndent = new char[100];
		if (indent != NULL)		strcpy (myIndent, indent);
		else					strcpy (myIndent, "\t\t");
										
		cout << "\n" << myIndent << " XSD-AttributeDefinition: "; 	if (name != NULL) cout << " [" << name << "]";
		if (fixed != NULL) {
			cout << "  fixed (" << fixed << ")";
		}
		if (isReference) cout << " is REFER ";  
		if (xType != NULL) {
			cout << " with *xType* ";
			strcat (myIndent, "\t");   
			xType->print(myIndent);   
		}
																			delete [] myIndent;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


XSDType::~XSDType() {}
XSDType::XSDType() {
			name = NULL; extensionOf = NULL; xRestriction = NULL; nst = NULL; isReference = false; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



XSDRestriction::~XSDRestriction() {}
XSDRestriction::XSDRestriction() {
			base = NULL; howSpecified = -1; minInclusive = 0.0; maxInclusive = 0.0; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

void
XSDRestriction::print(char *indent) {
																				char *myIndent = new char[100];
		if (indent != NULL)		strcpy (myIndent, indent);
		else					strcpy (myIndent, "\t\t");
										

	if (base != NULL) cout << "\n" << myIndent << " XSD-Restriction........ base: [" 
														<< base << "]  howSpecified: " << howSpecified;
	if (howSpecified == 0) {
		cout << "\n" << myIndent << " Specified as enumeration-" << enumeration.size() << ": "; cout << "[";
		for (int i=0,Z=enumeration.size(); i<Z; ++i) {
			cout << enumeration[i]; if (i != Z-1) cout << ", ";
		} cout << "]"; 
	}
	if (howSpecified == 1) {
		cout << "\n" << myIndent << " Specified as min/max values "; 
		cout << "   " << (float) minInclusive << " -- " << (float)maxInclusive;  
	}
	if (howSpecified == 2) {
		cout << "\n" << myIndent << " Specified as min/max values "; 
		cout << "   " << (int) minInclusive << " -- " << (int)maxInclusive;  
	}
	if (howSpecified == 3) {
		cout << "\n" << myIndent << " Specified as min/max values +ve "; 
		cout << "   " << (int) minInclusive << " -- " << (int)maxInclusive;  
	}
																				delete [] myIndent; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



void
XSDLeaf::print(char *indent) {
																				char *myIndent = new char[100];
		if (indent == NULL) strcpy (myIndent, "\t\t");
		else				strcpy (myIndent, indent);

												cout << "\n" << myIndent << " XSD-Leaf: ";
																					strcat (myIndent, "  ");
		if (xElem != NULL) { 
			cout << "\n" << myIndent << " xsd-Elem-Defn  [" << xElem->name << "] "; xElem->print(myIndent); 
		}
		if (xElemGrp != NULL) {
			cout << "\n" << myIndent << " xsd-ElemGroup-Defn "; 
			if (xElemGrp != NULL) cout<<"[" << xElemGrp->name << "] ";
			xElemGrp->print(myIndent); 
		}
		if (xAttr != NULL) {
			cout << "\n" << myIndent << " xsd-Attribute-Defn "; xAttr->print(myIndent); 
		}
		if (xAttrGrp != NULL) {
			cout << "\n" << myIndent << " xsd-Attribute-Group ";  xAttrGrp->print(myIndent);
		}
		if (xType != NULL) {
			cout << "\n" << myIndent << " xsd TYPE "; xType->print(myIndent);
		}
		if (oElem != NULL) {
			cout << "\n" << myIndent << " O-Elem ";
			oElem->printAttributes (); 
		}
																				delete [] myIndent;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


XSDElementGroup::~XSDElementGroup() {}
XSDElementGroup::XSDElementGroup() {
	name = NULL; isReference = false; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!

void
XSDElementGroup::print(char *indent) {
																				char *myIndent = new char[100];
				if (indent == NULL) strcpy (myIndent, "\t\t");
				else				strcpy (myIndent, indent); 
					
	cout << "\n" << myIndent << " Element Group ["; if (name != NULL) cout << name; cout << "]";
	cout << "\n" << myIndent << " Has (" << grpElementsV.size() << ") elements "; cout << "["; 
	for (int k=0; k<grpElementsV.size(); ++k) {
		cout << grpElementsV[k]->name; if (k != grpElementsV.size()-1) cout << ","; 
	} cout << "]  ";
	if (isReference) {
		cout << " >reference< "; 
	}			
	strcat (myIndent, "  "); 
	strcat (myIndent, name); 
	strcat (myIndent, ":"); 
	for (int k=0; k<grpElementsV.size(); ++k) {
			grpElementsV[k]->print(myIndent);
	}
																				delete [] myIndent;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


bool
XSDElementGroup::isGroupMember (char *gElemName) {
	for (int k=0; k<grpElementsV.size(); ++k) {
			if ( !strcmp (grpElementsV[k]->name, gElemName) ) {
				return true;	
			}	
	}
	return false; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


XSDElementDefinition*
XSDElementGroup::getGroupMember (char *gElemName) {
	for (int k=0; k<grpElementsV.size(); ++k) {
			if ( !strcmp (grpElementsV[k]->name, gElemName) ) {
				return grpElementsV[k];	
			}	
	}
	return NULL; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_






XSDAttributeGroup::~XSDAttributeGroup() {}
XSDAttributeGroup::XSDAttributeGroup() {
	name = NULL; isReference = false; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!

void
XSDAttributeGroup::print(char *indent) {
																				char *myIndent = new char[100];
				if (indent == NULL) strcpy (myIndent, "\t\t");
				else				strcpy (myIndent, indent); 
					
	cout << "\n" << myIndent << " Attribute Group ["; if (name != NULL) cout << name; cout << "]";
	cout << "\n" << myIndent << " Has (" << grpAttributesV.size() << ") elements "; cout << "["; 
	for (int k=0; k<grpAttributesV.size(); ++k) {
		cout << grpAttributesV[k]->name; if (k != grpAttributesV.size()-1) cout << ", "; 
	} cout << "]  ";
	if (isReference) {
		cout << " >reference< "; 
	}			
	strcat (myIndent, "  "); 
	strcat (myIndent, name); 
	strcat (myIndent, ":"); 
	for (int k=0; k<grpAttributesV.size(); ++k) {
			grpAttributesV[k]->print(myIndent);
	}
																				delete [] myIndent;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

bool
XSDAttributeGroup::isGroupMember (char *gAttrName) {
	for (int k=0; k<grpAttributesV.size(); ++k) {
			if ( !strcmp (grpAttributesV[k]->name, gAttrName) ) {
				return true;	
			}	
	}
	return false; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


XSDAttributeDefinition*
XSDAttributeGroup::getGroupMember (char *gAttrName) {
	for (int k=0; k<grpAttributesV.size(); ++k) {
			if ( !strcmp (grpAttributesV[k]->name, gAttrName) ) {
				return grpAttributesV[k];	
			}	
	}
	return NULL; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_






XSDNestedStructure::~XSDNestedStructure() {}
XSDNestedStructure::XSDNestedStructure() {
	isUnion = false; isSequence = false; isAnyOrder = false; 
						//xLeaf = NULL; xDecomposition = NULL; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


void
XSDNestedStructure::print(char *indent) {
																				char *myIndent = new char[100];
																if (indent == NULL) strcpy (myIndent, "\t\t");
																else				strcpy (myIndent, indent);
	cout << "\n" << myIndent << " Number of Leaves: " << xLeafV.size();
	if (isUnion) cout << " Union ";
	if (isSequence) cout << " isSequence ";
	if (isAnyOrder) cout << " isAnyOrder ";
	if (cardinalityStatus.size() > 0) {
		cout << "\n" << myIndent << "  " << "Cardinality Status ";
		for (int k=0; k<cardinalityStatus.size(); ++k) {
			cout << "\n" << myIndent << "\t" << cardinalityStatus[k] << "   " << min[k] << "  " << max[k];
		}
	}
	if (xLeafV.size() > 0)  {
		cout << "\n" << myIndent << "  " << "Printing the Leaves  " << xLeafV.size();
		strcat (myIndent, "   ");
		for (int k=0; k<xLeafV.size(); ++k) {
			cout << "\n" << myIndent << "Leaf (" << k << ") ";
			xLeafV[k]->print(myIndent);
		}
	}
																				delete [] myIndent;	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


XSDLeaf::~XSDLeaf() {}
XSDLeaf::XSDLeaf() {
			xElem = NULL; xElemGrp = NULL; xAttr = NULL; xAttrGrp = NULL; oElem = NULL; xType = NULL; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!




//XSDDecomposition::~XSDDecomposition() {}
//XSDDecomposition::XSDDecomposition() {
//}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!




XSDAllowedElement::XSDAllowedElement() {
		name = NULL; myID = 1; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

XSDAllowedElement::~XSDAllowedElement() {
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

void
XSDAllowedElement::print(char *indent) {
															char *myIndent = new char[100];		
															if (indent != NULL) strcpy (myIndent, indent);
															else				strcpy (myIndent, "\t\t");
															char *buf = new char[100];
	sprintf (buf, " xsdAllowedElement: [%2d] { %s }", myID, name);	cout <<"\n" << buf;	
																			int	F=strlen(buf); 
	if (allowedChildsN.size() > 0) { 
				cout << "\n";
				for (int i=0; i<F+1; ++i) cout << " "; 
				cout <<  allowedChildsN.size() << "-Allowed children: {"; 
				for (int i=0; i<allowedChilds.size(); ++i) {
							cout << " " << allowedChilds[i]->name; 
										if (i != allowedChildsN.size()-1) {
												cout << "\n";
														for (int i=0; i<F+22; ++i) cout << " "; 
										}
				}
				cout << "}"; 
	}
	if (allowedAttrs.size() > 0) {
				cout << "\n";
				for (int i=0; i<F+1; ++i) cout << " "; 
				cout <<  allowedAttrs.size() << "-Allowed attributes: {"; 
				for (int i=0; i<allowedAttrs.size(); ++i) {
					cout << " " << allowedAttrs[i]; 
												if (i != allowedAttrs.size()-1) {
																	cout << "\n";
															for (int i=0; i<F+24; ++i) cout << " "; 
												}
				}
				cout << "}"; 
	}
															delete [] buf;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

void
XSDAllowedElement::setName(char *n) {
			if (n==NULL) return;	if (name != NULL) delete [] name;
			name = new char[strlen(n)+1]; strcpy (name, n); 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


void
XSDAllowedElement::addChildName(char *n) {
			if (n==NULL) return;	
			allowedChildsN.push_back(new char[strlen(n)+1]); 
			strcpy (allowedChildsN.back(), n); 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

void
XSDAllowedElement::addAttributeName(char *n) {
			if (n==NULL) return;	
			allowedAttrs.push_back(new char[strlen(n)+1]); 
			strcpy (allowedAttrs.back(), n); 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



void
XSDAllowedElement::checkSchemaElementStructure (XMLelement	 *sElement, XSDparser *spc, int debug) {
																						if(debug>6) {
		cout << "\n\n Check-Schema-Element-Structure() "; sElement->printAttributes();
		this->print();	}
																		int	 		found;
																	vector<int>		matchedArray;
		// The child of sElement should be one of the allowable childs of this schema construct
		for (int c=0; c<sElement->childs.size(); ++c) {
																	found = -1;
			for (int m=0; m<allowedChilds.size(); ++m) {
				if (allowedChilds[m]->matchesElemName (sElement->childs[c]->name)) {
					found = m; break;
				}	
			}
				if (found == -1) { 
					cout << "\n ?????????????????????????  Strange child element [" << sElement->childs[c]->name<<"]"; 
					sElement->print();
					cout << "\n\n"; exit (0);
				} else {
					matchedArray.push_back (found); 
				}
		}//-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
		
		// Also verify its attributes: 
		for (int a=0; a<sElement->attributes.size(); ++a) {
																	found = -1;
			for (int m=0; m<allowedAttrs.size(); ++m) {
				if (!strcmp (sElement->attributes[a]->name, allowedAttrs[m])) {
					found = m; break;
				}	
			}
				if (found == -1) {
					  cout << "\n ?????????????????????????  Strange attribute [" 
						  		<< sElement->attributes[a]->name<<"]"; 
					  sElement->print();
					  cout << "\n\n"; exit (0);
				} else {
					// Some day.. we'll write code to validate the value of the attribute also,
					// as per any of the schema restrictions. 
				}
		}

		// Now recursively call this function for each of the found child elements 	
		for (int c=0; c<sElement->childs.size(); ++c) {
				allowedChilds[matchedArray[c]]->checkSchemaElementStructure (sElement->childs[c], spc);
		}
				
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!




bool
XSDElementDefinition::checkOtherPossibleAttributes (char *attrName) {
	
	if (!strcmp (attrName, "xmlns:xsi"))
		return true;
	else if (!strcmp (attrName, "xsi:noNamespaceSchemaLocation"))
		return true;
	else if (!strcmp (attrName, "xmlns"))
		return true;
	return false; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


bool	
XSDAllowedElement::matchesElemName (char *eName) {
		// Break the eName into its name space and actual Name;	Then match the two in its own lists. 
		// cout << "\n Matches-Elem-Name() => Given Name: " << eName;
		char 	*nspace 	= 	new char[strlen(eName)+1];
		char	*onlyName 	= 	new char[strlen(eName)+1]; 	
																			bool	gotNS = false; 
																			int		k = 0; 
		for (int i=0,Z=strlen(eName); i<Z; ++i) {		
				if (eName[i]==':') {
					onlyName[k] = '\0'; 
					strcpy (nspace, onlyName); k = 0;
					gotNS = true; continue;
				}
				onlyName[k++] = eName[i]; 
		}	
		onlyName[k] = '\0';
		
		if (gotNS) {
			//cout << "\n Matches-Elem-Name() => Name space: " << nspace;
		}			
		//cout << "\n Matches-Elem-Name() => Element name: " << onlyName;
						
														bool matchedOnlyName = false, alsoMatchedNamespace = false;
				if (!strcmp(onlyName, this->name)) {
											matchedOnlyName = true;
											// Also check if the name space matches the allowable....
											for (int k=0; k<allowedNameSpaces.size(); ++k) {
												if (!strcmp (allowedNameSpaces[k], nspace)) {
													alsoMatchedNamespace = true; break; 
												}
											}
											if (allowedNameSpaces.size() == 0) {
												alsoMatchedNamespace = true;
											}
				}//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - 
																delete [] nspace; delete [] onlyName;
				if (matchedOnlyName && alsoMatchedNamespace) return true;
				else									 	 return false; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


bool
XSDparser::matchesElementNameOnly (char *eName, char *eNameWithoutNamespace) {
		char 	*nspace 	= 	new char[strlen(eName)+1];
		char	*onlyName 	= 	new char[strlen(eName)+1]; 	
																			bool	gotNS = false; 
																			int		k = 0; 
		for (int i=0,Z=strlen(eName); i<Z; ++i) {		
				if (eName[i]==':') {
					onlyName[k] = '\0'; 
					strcpy (nspace, onlyName); k = 0;
					gotNS = true; continue;
				}
				onlyName[k++] = eName[i]; 
		}
		onlyName[k] = '\0';
		//cout << "\n Attempting to match: " << onlyName << "-----" << eNameWithoutNamespace; 
		if (!strcmp(onlyName, eNameWithoutNamespace)) {
									delete [] nspace; delete [] onlyName; 
				return true;
		}
									delete [] nspace; delete [] onlyName; 
		   		return false;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


void
XSDparser::removeNameSpaceQualifier (char *eName) {
		for (int i=0,Z=strlen(eName); i<Z; ++i) {		
				if (eName[i]==':') {
					// Shift the entire string from this point onwards
					Z = Z-i;
					for (int k=0; k<Z; ++k) {
						eName[k] = eName[++i];
					}
					break; 
				}
		}
		//cout << "\n After name space removal: " << eName; getchar(); 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!

SchemaDynamicStructures::SchemaDynamicStructures() {
		eleM = NULL;
		xsdElem = NULL;
		attr = NULL;
		xsdAttr = NULL;
		xType = NULL; 
		fileNameInWhichErrorOccurred = NULL; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
void
SchemaDynamicStructures::reset() {
				xsdElem = 	NULL;
				eleM	=	NULL; 
				attr	=	NULL;
				xsdAttr =	NULL;
				xType	=	NULL; 
				xLeaf	=	NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


void
XSDparser::print() {
	cout << "\n\n -------------------------- Printing the XSD parser information --------------------";	
	cout << "\n\t\t With [" << xsdElementDefsV.size() << "] element definitions "; 			
	cout << "\n\t\t With [" << xsdAttributeDefsV.size() << "] attribute definitions "; 			
	cout << "\n\t\t With [" << xsdElementGroupsV.size() << "] element group definitions "; 			
	cout << "\n\t\t With [" << xsdAttributeGroupsV.size() << "] attribute group definitions "; 			
	cout << "\n\t\t With [" << xsdTypesV.size() << "] type definitions "; 			
	cout << "\n\t\t With [" << xsdSimpleDataTypesV.size() << "] simple data types "; 			
	cout << "\n\t\t With [" << xsdAllowedElementsV.size() << "] allowed elements ";
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
	
	
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
void
XSDparser::extractSchemaDictatedInformation (vector<XMLelement*> & schemaElementList, XMLparser *xmlParser) { 
																									if(debug>2)
	cout << "\n\n ------------------------- Extract Schema Element Information () -------------------- ";
	stack<XMLelement*>	elmStack;
	XMLelement			*eleM; 

						vector<XMLelement*>		 xxSchemaElementsV;
						vector<char*>			 requiredAttrValues;
	
				for (int i=0; i<schemaElementList.size(); ++i) {
						xmlParser->searchElement ("schema", schemaElementList[i], 
													requiredAttrValues, xxSchemaElementsV, true); 	
				} //--  --  --  --  --  --  --  --  --  --  --  --  --  --  -- 
																										if(debug>2)
				cout << "\n\n---------------------------------------------------------------------- All xx:schema elements obtained from the schema ";
				for (int i=0; i<xxSchemaElementsV.size(); ++i) {
													if(debug>5)
					xxSchemaElementsV[i]->print();
					xxSchemaElementsV[i]->myID = i;  
				} //--  --  --  --  --  --  --  --  --  --  --  --  --  --  --
	// ----------------- Now collect all the information that you can collect from the schema ---------------
																			XMLelement	*schelToAnalyze;
	for (int xx=0; xx < xxSchemaElementsV.size(); ++xx) {
	for (int cc=0; cc<xxSchemaElementsV[xx]->childs.size(); ++cc) {
		schelToAnalyze = xxSchemaElementsV[xx]->childs[cc]; 
																									if(debug>2) {
		cout << "\n\n --------------------------- started processing it.."; schelToAnalyze->printAttributes();}
			 
			 if (matchesElementNameOnly (schelToAnalyze->name, "element")) {
				 																					if(debug>5)
			 		cout << "\n extractSchemaDictatedInformation() => Got an element to process: ";
					XSDElementDefinition   *xsdElemDef = attemptToMakeXSDElementDefn (schelToAnalyze);  
					if (xsdElemDef == NULL) {
						// We need to save this element as oElem. 
					} else {
												if(debug>5)
						xsdElemDef->print("\t");   
						this->xsdElementDefsV.push_back(xsdElemDef);
					}
			 } else
			 if (matchesElementNameOnly (schelToAnalyze->name, "attribute")) {
				 																					if(debug>5)
			 		cout << "\n extractSchemaDictatedInformation() => Got an attribute to process: ";
					XSDAttributeDefinition  *xsdAttrDef = attemptToMakeXSDAttributeDefn (schelToAnalyze);  
																									if(debug>5)
								 			 xsdAttrDef->print("\t"); 
											 this->xsdAttributeDefsV.push_back (xsdAttrDef); 
			 } else
			 if (matchesElementNameOnly (schelToAnalyze->name, "complexType")) {
				 																					if(debug>5)
			 		cout << "\n extractSchemaDictatedInformation() => Got a complexType to process: ";
				 	XSDType 	*xType = attemptToMakeXSDType (schelToAnalyze);  
																									if(debug>5)
								 xType->print("\t"); 
								 this->xsdTypesV.push_back (xType); 
			 } else
			 if (matchesElementNameOnly (schelToAnalyze->name, "simpleType")) {
				 																					if(debug>5)
			 		cout << "\n extractSchemaDictatedInformation() => Got a simpleType to process: ";
				 	XSDType 	*xType = attemptToMakeXSDType (schelToAnalyze);  
																									if(debug>5)
								 xType->print("\t"); 
								 this->xsdTypesV.push_back (xType); 
			 } else
			 if (matchesElementNameOnly (schelToAnalyze->name, "elementGroup")) {
				 																					if(debug>5)
			 		cout << "\n extractSchemaDictatedInformation() => Got a elementGroup to process: ";
				 	XSDElementGroup 	*xElemGrp = attemptToMakeXSDElementGroup (schelToAnalyze);  
																									if(debug>5)
										 xElemGrp->print("\t"); 
								 this->xsdElementGroupsV.push_back (xElemGrp); 
			 } else
			 if (matchesElementNameOnly (schelToAnalyze->name, "attributeGroup")) {
				 																					if(debug>5)
			 		cout << "\n extractSchemaDictatedInformation() => Got a attributeGroup to process: ";
				 	XSDAttributeGroup 	*xAttrGrp = attemptToMakeXSDAttributeGroup (schelToAnalyze);  
																									if(debug>5) 
										 xAttrGrp->print("\t"); 
								 this->xsdAttributeGroupsV.push_back (xAttrGrp); 
			 }
	}
	}
		// -------------- We have finished one round of parsing for the schema. 
		// -------------- The left over work concerned with forward referencing needs to be done now. 	
			for (int k=0; k<sdd->incompleteWorksV.size(); ++k) {
				if (!strcmp (sdd->incompleteWorksV[k]->workName, "extension")) {
					//cout << "\n Doing processing in the second pass: "; sdd->incompleteWorksV[k]->print();
										XMLelement *celem = sdd->incompleteWorksV[k]->xelem; 
										XSDType	   *xType = sdd->incompleteWorksV[k]->xType;
											char *typeName = celem->getAttributeValue("base"); 
												if (typeName != NULL) { // Extension of this type...
													XSDType *toExtendType = getXSDType (typeName);
													if (toExtendType != NULL) {
														xType->extensionOf = toExtendType;
														extendXSDType (xType, toExtendType);
														fillUpDetailsForXSDType (xType, celem);//Carry on
													} else {
														XSDElementDefinition *toExtendElem = 
																			getXSDElementDefinition (typeName);
														if (toExtendElem != NULL) {
															xType->extensionOf = toExtendElem->xType;
															extendXSDType (xType, toExtendElem->xType);
															fillUpDetailsForXSDType (xType, celem);	
															//cout << "\n --------------------------------------";
															//xType->print();
															//cout << "\n --------------------------------------"<<flush;
														} else {
				 											sdd->eleM = celem;  
				 											this->setString ( sdd->fileNameInWhichErrorOccurred, 
																			 this->schemaFileName); 
				 sprintf (buf, " fillUpDetailsFor-XSD-Type-Defn() => The base [%s] of extension has not been defined ", 
						 													typeName); 
														 	 popError (10, buf);
														 	 assert (1==2); 
														}
													}
												}
		
							
				}	
			}
			
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



XSDElementDefinition*
XSDparser::attemptToMakeXSDElementDefn (XMLelement *elem) {
		// Cases to handle: 
		// Case 1: If there is an attribute ref, then return NULL
		// Case 2: If there is an attribute name, then instantiate XSDElementDefinition
								// Now comes the problem of handling the type. 
								// 			That can be specified directly, or to be constructed. 
																					char 	*value; 
																	XSDElementDefinition	*xsdElemDef; 
																							sdd->reset();
		xsdElemDef = new XSDElementDefinition();

										value = elem->getAttributeValue("ref"); 
												if (value != NULL) { // This is a reference to the element. 
														xsdElemDef->setString(xsdElemDef->name, value); 
														xsdElemDef->isReference = true; 
														assert (elem->childs.size() == 0); 
														return 	xsdElemDef; 	
												}
		
			
			value = elem->getAttributeValue("name"); 	
		if (value != NULL) {
			xsdElemDef->setString(xsdElemDef->name, value); 
		}
									
			value = elem->getAttributeValue("type"); 	
		if (value != NULL) {
			xsdElemDef->setString(xsdElemDef->xTypeName, value); 
			xsdElemDef->xType = new XSDType();
			setString(xsdElemDef->xType->name, value); // May be simple type or a reference. 
			xsdElemDef->xType->isReference = true; 	// If not found in reference list, then it is a simple type. 
		}
		// Check for a child element. If there is a child element complexType, then expect the XSDType object
		// to be returned. If the child element says simpleType.. even then expect XSDType object to be returned. 	
		for (int c=0; c<elem->childs.size(); ++c) {
			 if (matchesElementNameOnly (elem->childs[c]->name, "complexType") || 
			 	 matchesElementNameOnly (elem->childs[c]->name, "simpleType") 
					 ) {
				 	if (xsdElemDef->xType != NULL) {
						sdd->eleM = elem; 
						sdd->xsdElem = xsdElemDef;
						popError (10, " Multiple specification of TYPE of the element.... Check Schema ");
					}	
																								if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Element-Defn() => Got a complex/simple:: Type.. ";
					xsdElemDef->xType = attemptToMakeXSDType (elem->childs[c]);  
			 } else {
				 						if(debug>5)
				elem->childs[c]->print(); 
				sdd->eleM = elem->childs[c];  
				 this->setString (sdd->fileNameInWhichErrorOccurred, this->schemaFileName); 
				popError (10, " attemptToMake-XSD-Element-Defn() => Child element NOT HANDLED ");
			 	assert (1==2); // No other child element is allowed. 
			 }
		}			
				
		return 	xsdElemDef; 	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!





void
XSDElementDefinition::setString(char *& tString, char *gString) {
		if (tString != NULL) delete [] tString; 
		tString = new char[strlen(gString)+1];
		strcpy (tString, gString); 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!

void
XSDElementDefinition::print(char *indent) {
																	char *myIndent = new char[100];
	if (indent != NULL) {
		strcpy (myIndent, indent); 
	} else strcpy (myIndent, "\t\t"); 
		
	cout << "\n" << myIndent << " XSDElementDefinition: "; 
	if (name != NULL) cout << " [" << name << "]"; 		
	if (xTypeName != NULL) cout << "   type: " << xTypeName; 
	if (isReference) cout << "  >reference< ";
									strcat (myIndent, "  ");
	if (xType != NULL) xType->print(myIndent); 
																	delete [] myIndent;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


void
XSDType::setString(char *& tString, char *gString) {
		if (tString != NULL) delete [] tString; 
		tString = new char[strlen(gString)+1];
		strcpy (tString, gString); 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!

void
XSDparser::setString(char *& tString, char *gString) {
		if (tString != NULL) delete [] tString; 
		tString = new char[strlen(gString)+1];
		strcpy (tString, gString); 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



void
XSDType::print(char *indent) {
																	char *myIndent = new char[100];
	if (indent != NULL) {
		strcpy (myIndent, indent); 
	} else strcpy (myIndent, "\t\t"); 
		
	cout << "\n" << myIndent << "  XSDType: ";
	if (name != NULL) cout << " [" << name << "]"; 
	if (isReference) cout << "  reference/in-built ";
											strcat (myIndent, "  ");
	if (extensionOf != NULL) { 
								char *buf = new char[200];		strcpy (buf, myIndent); strcat (buf, "Extension");
			extensionOf->print(buf);
								delete [] buf;
	}
	if (xRestriction != NULL) xRestriction->print(myIndent);
	if (nst != NULL) nst->print(myIndent);
	if (attributesV.size() > 0) {
			cout << "\n" << myIndent << " Has attributes " << attributesV.size();
			for (int i=0; i<attributesV.size(); ++i) 
				attributesV[i]->print(myIndent);
	}
	if (attrGroupsV.size() > 0) {
			cout << "\n" << myIndent << " Has attribute-Groups " << attrGroupsV.size();
			for (int i=0; i<attrGroupsV.size(); ++i) 
				attrGroupsV[i]->print(myIndent);
	}
																	delete [] myIndent;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


XSDAttributeDefinition*
XSDparser::attemptToMakeXSDAttributeDefn (XMLelement *elem) {
				
																							char 	*value; 
									//	value = elem->getAttributeValue("ref"); 
									//			if (value != NULL) { // This is a reference to the element. 
									//					return NULL; 	
									//			}
																	XSDAttributeDefinition		*xsdAttr; 
																							sdd->reset();
		xsdAttr = new XSDAttributeDefinition();
			
			value = elem->getAttributeValue("name"); 	
		if (value != NULL) {
			setString(xsdAttr->name, value); 
		}

		value = elem->getAttributeValue("ref"); 	
		if (value != NULL) {
			setString(xsdAttr->name, value); 
			xsdAttr->isReference = true;
		}
		value = elem->getAttributeValue("fixed"); 	
		if (value != NULL) {
			setString(xsdAttr->fixed, value); 
		}

		value = elem->getAttributeValue("type"); 	
		if (value != NULL) {
			if (xsdAttr->xType != NULL) {
				sdd->eleM = elem; sdd->xsdAttr = xsdAttr; 
				popError (10, " The element has an already assigned TYPE ??? ");
			}
			xsdAttr->xType = new XSDType;  
			setString (xsdAttr->xType->name, value);
			xsdAttr->xType->isReference = true; // Simple data-type OR  Defined-type. 
		}
		
		for (int c=0; c<elem->childs.size(); ++c) {
			 if (matchesElementNameOnly (elem->childs[c]->name, "simpleType")  ||
			     matchesElementNameOnly (elem->childs[c]->name, "complexType") 
					 ) {
				 																							if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Attribute-Defn() => Got an XSD-TYPED-attribute.. ";
					XSDType  *xsdType = attemptToMakeXSDType (elem->childs[c]);  
					if (xsdAttr->xType != NULL) {
						sdd->eleM = elem; sdd->xsdAttr = xsdAttr; 
						popError (10, " The element has an already assigned TYPE ??? ");
					}	
					if (xsdType != NULL)  xsdAttr->xType = xsdType;  // Do not overwrite previous one? 
			 } else {
				 sdd->eleM = elem;  
				 this->setString (sdd->fileNameInWhichErrorOccurred, this->schemaFileName); 
				 sprintf (buf, " attemptToMake-XSD-Attribute-Defn() => Child [%s] NOT HANDLED ",elem->childs[c]->name);
			 	 popError (10, buf);
				 assert (1==2); // No other child element is allowed. 
			 }
		}
		
		
																				return xsdAttr;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


XSDType*
XSDparser::attemptToMakeXSDType (XMLelement *elem) {
		// Check if the type has got any name: 
																	XSDType		*xType; 
		xType = new XSDType();
		
																							char 	*value; 
																							sdd->reset();
										value = elem->getAttributeValue("ref"); 
												if (value != NULL) { // This is a reference to the element. 
													xType->setString(xType->name, value); 
													xType->isReference = true; 
														assert (elem->childs.size() == 0);
														return xType;
												}
												
		
			
			value = elem->getAttributeValue("name"); 	
		if (value != NULL) {
			xType->setString(xType->name, value); 
		}


		this->fillUpDetailsForXSDType (xType, elem); 		
				
		return 	xType; 	
	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!





void
XSDparser::fillUpDetailsForXSDType (XSDType *xType, XMLelement *elem) {
	
			// Check for a child element. 
		for (int c=0; c<elem->childs.size(); ++c) {
			 if (matchesElementNameOnly (elem->childs[c]->name, "sequence") ) {
				 																			if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Type-Defn() => Got a Sequence.. ";
					XSDNestedStructure  *gotNstStructure = attemptToMakeXSDNestedSt (elem->childs[c]);  
														if (xType->nst == NULL) xType->nst = gotNstStructure;
														else xType->nst->addToNestedStructure (gotNstStructure);
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "union") ) {	
				 																			if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Type-Defn() => Got a Union.. ";
					//xType->nst = attemptToMakeXSDNestedSt (elem->childs[c]);  
					XSDNestedStructure  *gotNstStructure = attemptToMakeXSDNestedSt (elem->childs[c]);  
														if (xType->nst == NULL) xType->nst = gotNstStructure;
														else xType->nst->addToNestedStructure (gotNstStructure);

			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "restriction") ) {
				 																			if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Type-Defn() => Got a Restriction.. ";
					xType->xRestriction = attemptToMakeXSDRestriction (elem->childs[c]);  
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "attribute") ) {
				 																			if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Type-Defn() => Got an attribute.. ";
					XSDAttributeDefinition  *xsdAttr = attemptToMakeXSDAttributeDefn (elem->childs[c]);  
					if (xsdAttr != NULL)  xType->attributesV.push_back (xsdAttr);  
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "attributeGroup") ) {
				 																			if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Type-Defn() => Got an attributeGroup.. ";
					XSDAttributeGroup  *xsdAttrGrp = attemptToMakeXSDAttributeGroup (elem->childs[c]);  
					if (xsdAttrGrp != NULL)  xType->attrGroupsV.push_back (xsdAttrGrp);  
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "complexContent") ) {
								XMLelement *celem = elem->childs[c]; 
								for (int f=0; f<celem->childs.size(); ++f) {
									if (matchesElementNameOnly(celem->childs[f]->name, "extension")) {
										char *typeName = celem->childs[f]->getAttributeValue("base"); 
												if (typeName != NULL) { // Extension of this type...
													XSDType *toExtendType = getXSDType (typeName);
													if (toExtendType != NULL) {
														xType->extensionOf = toExtendType;
														extendXSDType (xType, toExtendType);
														fillUpDetailsForXSDType (xType, celem->childs[f]);//Carry on
													} else {
														XSDElementDefinition *toExtendElem = 
																			getXSDElementDefinition (typeName);
														if (toExtendElem != NULL) {
															xType->extensionOf = toExtendElem->xType;
															extendXSDType (xType, toExtendElem->xType);
															fillUpDetailsForXSDType (xType, celem->childs[f]);	
															//cout << "\n --------------------------------------";
															//xType->print();
															//cout << "\n --------------------------------------"<<flush;
														} else {
															sdd->incompleteWorksV.push_back (
															new IncompleteWork (celem->childs[f], xType, "extension"));
																								if (1==2) {
				 											sdd->eleM = celem->childs[f];  
				 											this->setString ( sdd->fileNameInWhichErrorOccurred, 
																			 this->schemaFileName); 
				 sprintf (buf, " fillUpDetailsFor-XSD-Type-Defn() => The base [%s] of extension has not been defined ", 
						 													typeName); 
														 	 popError (10, buf);
														 	 assert (1==2); 
																								}
														}
													}
												}
									}
								}
			 } else {
				 sdd->eleM = elem;  
				 this->setString (sdd->fileNameInWhichErrorOccurred, this->schemaFileName); 
				 sprintf (buf, " fillUpDetailsFor-XSD-Type-Defn() => Child [%s] NOT HANDLED ", elem->childs[c]->name); 
			 	 popError (10, buf);
			 	 assert (1==2); // No other child element is allowed. 
			 }
		}			
				

}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


void
XSDparser::extendXSDType (XSDType *newerType, XSDType *olderType) {
	 
	if (olderType->nst != NULL) {
	     if (newerType->nst == NULL) 	newerType->nst = new XSDNestedStructure(); 
		 newerType->nst->addToNestedStructure (olderType->nst);
				// for (int k=0; k<olderType->nst->xLeafV.size(); ++k) {
			 		//	newerType->nst->xLeafV.push_back (olderType->nst->xLeafV[k]);
		 		//}
	}
	 
	for (int k=0; k<olderType->attributesV.size(); ++k) {
		newerType->attributesV.push_back (olderType->attributesV[k]); 
	}

	for (int k=0; k<olderType->attrGroupsV.size(); ++k) {
		newerType->attrGroupsV.push_back (olderType->attrGroupsV[k]); 
	}
	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


void
XSDNestedStructure::addToNestedStructure (XSDNestedStructure *givenNstStructure) {
		 for (int k=0; k<givenNstStructure->xLeafV.size(); ++k) {
		 		this->xLeafV.push_back (givenNstStructure->xLeafV[k]);
		 }
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



XSDNestedStructure*
XSDparser::attemptToMakeXSDNestedSt (XMLelement *elem) {
					
																		XSDNestedStructure		*xsdNst; 
																				char			*value;   
																							sdd->reset();
		xsdNst = new XSDNestedStructure();
		
			if (matchesElementNameOnly(elem->name, "sequence"))	xsdNst->isSequence = true;
			if (matchesElementNameOnly(elem->name, "union"))	xsdNst->isUnion = true;
									
		for (int c=0; c<elem->childs.size(); ++c) {
																			XSDLeaf 	*myLeaf = new XSDLeaf(); 
			 if (matchesElementNameOnly (elem->childs[c]->name, "element") ) {
				 																if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-NestedSt() => element ";
				 	XSDElementDefinition 	*xsdElemDef = attemptToMakeXSDElementDefn (elem->childs[c]); 
					if (xsdElemDef != NULL) {
									myLeaf->xElem = xsdElemDef;
					} else {  
									myLeaf->oElem = elem->childs[c];
					}
																		xsdNst->xLeafV.push_back (myLeaf); 
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "elementGroup") ) {
				 																if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-NestedSt() => element-Group ";
				 	XSDElementGroup 	*xsdElemGrp = attemptToMakeXSDElementGroup (elem->childs[c]); 
					if (xsdElemGrp != NULL) {
									myLeaf->xElemGrp = xsdElemGrp;
					} else {
									myLeaf->oElem = elem->childs[c];
					}  
																		xsdNst->xLeafV.push_back (myLeaf); 
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "attribute") ) {
				 																if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-NestedSt() => attribute ";
				 	XSDAttributeDefinition 	*xsdAttrDef = attemptToMakeXSDAttributeDefn (elem->childs[c]); 
					if (xsdAttrDef != NULL) {
									myLeaf->xAttr = xsdAttrDef;
					} else {
									myLeaf->oElem = elem->childs[c];
					}
																		xsdNst->xLeafV.push_back (myLeaf); 
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "attributeGroup") ) {
				 																if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-NestedSt() => Attribute Group ";
				 	XSDAttributeGroup 	*xsdAttrGrp = attemptToMakeXSDAttributeGroup (elem->childs[c]); 
					if (xsdAttrGrp != NULL) {
									myLeaf->xAttrGrp = xsdAttrGrp;
					} else {
									myLeaf->oElem = elem->childs[c];
					}
																		xsdNst->xLeafV.push_back (myLeaf); 
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "simpleType") ||
			 	 matchesElementNameOnly (elem->childs[c]->name, "complexType") 
					 ) {
				 																if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-NestedSt() => xType(branching) ";
				 	XSDType 	*xType = attemptToMakeXSDType (elem->childs[c]); 
					if (xType != NULL) {
									myLeaf->xType = xType;
					} else {
									myLeaf->oElem = elem->childs[c];
					}
																		xsdNst->xLeafV.push_back (myLeaf); 
			 } 
			 else {
				 sdd->eleM = elem;  
				 this->setString (sdd->fileNameInWhichErrorOccurred, this->schemaFileName); 
				 sprintf (buf, " attemptToMake-XSD-NestedSt() => Child [%s] NOT HANDLED ", elem->childs[c]->name); 
			 	 popError (10, buf);
			 		assert (1==2); // No other child element is allowed. 
			 }
		}			
				
		return 	xsdNst; 	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



XSDElementGroup*
XSDparser::attemptToMakeXSDElementGroup (XMLelement *elem) {
						
	assert (elem->childs.size()<=1); 	
																		XSDElementDefinition	*xsdElem;
																		XSDElementGroup			*xsdGroup;
																							sdd->reset();
		xsdGroup = new XSDElementGroup();																
					char *value = elem->getAttributeValue("name");
						if(value != NULL) {
							setString (xsdGroup->name, value);
						}					
					value = elem->getAttributeValue("ref");
						if(value != NULL) {
							setString (xsdGroup->name, value);
							xsdGroup->isReference = true; 
						}					
														if (elem->childs.size()==0) return xsdGroup; 
	XMLelement *seq = elem->childs[0];	
	for (int k=0; k<seq->childs.size(); ++k) {
		assert (matchesElementNameOnly(seq->childs[k]->name, "element")); 
		xsdElem = attemptToMakeXSDElementDefn (seq->childs[k]);
		xsdGroup->grpElementsV.push_back (xsdElem);
	}
		return xsdGroup;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


XSDAttributeGroup*
XSDparser::attemptToMakeXSDAttributeGroup (XMLelement *elem) {
																		XSDAttributeDefinition	*xsdAttr;
																		XSDAttributeGroup		*xsdGroup;
		xsdGroup = new XSDAttributeGroup();																
					char *value = elem->getAttributeValue("name");
						if(value != NULL) {
							setString (xsdGroup->name, value);
						}					
					value = elem->getAttributeValue("ref");
						if(value != NULL) {
							setString (xsdGroup->name, value);
							xsdGroup->isReference = true; 
						}					
	for (int k=0; k<elem->childs.size(); ++k) {
		assert (matchesElementNameOnly(elem->childs[k]->name, "attribute")); 
		xsdAttr = attemptToMakeXSDAttributeDefn (elem->childs[k]);
		xsdGroup->grpAttributesV.push_back (xsdAttr);
	}
		return xsdGroup;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!







XSDRestriction*
XSDparser::attemptToMakeXSDRestriction (XMLelement *elem) {
			
																		XSDRestriction		*xRestriction; 
																				char		*value;   
		xRestriction = new XSDRestriction();
			
			value = elem->getAttributeValue("base"); 	
		if (value != NULL) {
			setString(xRestriction->base, value); 
			if (matchesElementNameOnly(value, "decimal"))	xRestriction->howSpecified = 1;
			if (matchesElementNameOnly(value, "integer"))	xRestriction->howSpecified = 2;
			if (matchesElementNameOnly(value, "positiveInteger"))	xRestriction->howSpecified = 3;
		}
									
		// Check for a child element. If there is a child element complexType, then expect the XSDType object
		// to be returned. If the child element says simpleType.. even then expect XSDType object to be returned. 	
		for (int c=0; c<elem->childs.size(); ++c) {
			 if (matchesElementNameOnly (elem->childs[c]->name, "enumeration") ) {
				 																if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Restriction() => Enumeration ";
																XMLelement	*enumE = elem->childs[c];
						//Take every child of this element and push it in the vector: 
										value = enumE->getAttributeValue("value"); 	
										if (value != NULL) {
											xRestriction->enumeration.push_back(value); 
										}
						xRestriction->howSpecified = 0; 
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "minInclusive") ) {
				 																if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Restriction() => minInclusive ";
										value = elem->childs[c]->getAttributeValue("value"); 	
										if (value != NULL) {
											sscanf (value, "%f", & xRestriction->minInclusive); 
										}
			 } else
			 if (matchesElementNameOnly (elem->childs[c]->name, "maxInclusive") ) {
				 																if(debug>5)
			 		cout << "\n\t\t\t attemptToMake-XSD-Restriction() => maxInclusive ";
										value = elem->childs[c]->getAttributeValue("value"); 	
										if (value != NULL) {
											sscanf (value, "%f", & xRestriction->maxInclusive); 
										}
			 } 
			 else {
				 sdd->eleM = elem;  
				 this->setString (sdd->fileNameInWhichErrorOccurred, this->schemaFileName); 
				 sprintf (buf, "attemptToMake-XSD-Restriction() => Child [%s] NOT HANDLED ", elem->childs[c]->name); 
			 	 popError (10, buf);
			 	assert (1==2); // No other child element is allowed. 
			 }
		}			
				
		return 	xRestriction; 	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


void
XSDparser::reset() {
				if (schemaFileName != NULL) delete [] schemaFileName; schemaFileName = NULL;
				
			for (int k=0; k<xsdElementDefsV.size(); ++k) delete xsdElementDefsV[k];
																xsdElementDefsV.clear(); 	
			for (int k=0; k<xsdAttributeDefsV.size(); ++k) delete xsdAttributeDefsV[k];
																xsdAttributeDefsV.clear(); 	
			for (int k=0; k<xsdElementGroupsV.size(); ++k) delete xsdElementGroupsV[k];
																xsdElementGroupsV.clear(); 	
			for (int k=0; k<xsdAttributeGroupsV.size(); ++k) delete xsdAttributeGroupsV[k];
																xsdAttributeGroupsV.clear(); 	
			for (int k=0; k<xsdTypesV.size(); ++k) delete xsdTypesV[k];
																xsdTypesV.clear(); 	
			if (xmlParser != NULL) xmlParser->reset(); 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!

void	
XMLparser::verifyAgainstSchema (char *schemaFileName, int debug) { 
																	assert (schemaFileName != NULL);
		if (xsdParser == NULL) {
							xsdParser 	 = 	new XSDparser(); 
					xsdParser->xmlParser =  new XMLparser();
													xsdParser->setString(xsdParser->schemaFileName, schemaFileName);
					if (!xsdParser->xmlParser->readXMLdocument (schemaFileName)) {
						cout << "\n\n"; exit (0);
					}
		} else {
			if (xsdParser->schemaFileName != NULL) {
					if (!strcmp (xsdParser->schemaFileName, schemaFileName)) {
																								if(debug>0)
						cout << "\n\n Schema file [" << schemaFileName << "] has been already read ";
					} else {
																							if(debug>0)
						cout << "\n\n Reading new Schema file [" << schemaFileName << "]  ";
						xsdParser->reset();
											xsdParser->setString(xsdParser->schemaFileName, schemaFileName);
						if (xsdParser->xmlParser == NULL)
							xsdParser->xmlParser = new XMLparser();
						if (!xsdParser->xmlParser->readXMLdocument (schemaFileName)) {
							cout << "\n\n"; exit (0); 
						}
					}		
			}
		}
			
						if (this->fileName == NULL) {
							this->fileName = new char[1000];  
							strcpy (fileName, "Schema-data");
						}
								xsdParser->setString (xsdParser->sdd->fileNameInWhichErrorOccurred, this->fileName);
																						xsdParser->debug =debug;
							//xsdParser->xmlParser->print();															
																									  
																							if(debug>0) {
		cout << "\n -------------------- Doing a SYNTACTIC checking of the SCHEMA ------------------";		
		cout << "\n -------------------- This is in no way exhaustive.  ----------------------------";		
		cout << "\n -------------------- Please check it manually also. ----------------------------";		
		cout << "\n --------------------------------------------------------------------------------";		
																							}
		
		vector<XMLelement*> & schemaElementList = xsdParser->xmlParser->elementList; 
	
				for (int i=0; i<schemaElementList.size(); ++i) {
					xsdParser->checkSchemaStructure (schemaElementList[i]); 
				}
				xsdParser->extractSchemaDictatedInformation (schemaElementList, this); 
							//xsdParser->print();															
																								if(debug>2) {
	cout << "\n __________________________________________________________________________________";
	cout << "\n                   The Schema seems to be O.K.  ";
	cout << "\n ----------------------------------------------------------------------------------";  
	cout << "\n ----------------------------------------------------------------------------------";  
	this->xsdParser->print(); 
																								}
			//cout << "\n\n"; exit (0);
			
	for (int e=0; e<elementList.size(); ++e) {
		xsdParser->verifyElementWithSchemaSpecs (elementList[e]);
	}	
																								if(debug>0) 
	cout << "\n __________________________________________________________________________________";
	cout << "\n                   Schema Validation of [__" << this->fileName << "__]  against  [__" 
														<< this->xsdParser->schemaFileName << "__]  is  PASSED  ";
																								if(debug>0) 
	cout << "\n ----------------------------------------------------------------------------------";  
																								
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_




void	
XMLparser::verifyAgainstSchema (vector<XMLelement*> & elementList, 
								vector<XMLelement*> & schemaElementList) { 
			
				xsdParser 		= 	new XSDparser(); 
		
		cout << "\n -------------------- Doing a SYNTACTIC checking of the SCHEMA ------------------";		
		cout << "\n -------------------- This is in no way exhaustive.  ----------------------------";		
		cout << "\n -------------------- Please check it manually also. ----------------------------";		
		cout << "\n --------------------------------------------------------------------------------";		

				for (int i=0; i<schemaElementList.size(); ++i) {
					xsdParser->checkSchemaStructure (schemaElementList[i]); 
				}
				xsdParser->extractSchemaDictatedInformation (schemaElementList, this); 
	cout << "\n __________________________________________________________________________________";
	cout << "\n                   The Schema seems to be O.K.  ";
	cout << "\n ----------------------------------------------------------------------------------";  
	cout << "\n ----------------------------------------------------------------------------------";  
	this->xsdParser->print(); 
			//cout << "\n\n"; exit (0);
			
	for (int e=0; e<elementList.size(); ++e) {
		xsdParser->verifyElementWithSchemaSpecs (elementList[e]);
	}	
	cout << "\n __________________________________________________________________________________";
	cout << "\n                   Schema Validation of XML data input:  PASSED  ";
	cout << "\n ----------------------------------------------------------------------------------";  

}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_




//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
void
XSDparser::verifyElementWithSchemaSpecs (XMLelement *elem, XSDElementDefinition *xsdElemg) {
																		
				 																				if(debug>5) 
	cout << "\n\n -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ "; if(debug>3)
	cout << "\n ------------------- verifyElementWithSchemaSpecs() ------" << elem->name << "------";if(debug>5)
	elem->print();

   																		sdd->eleM = elem;	
															XSDElementDefinition	*xsdElem;
															XSDAttributeDefinition	*xsdAttr; 			
	// First get the schema element definition for this element. 
						if (xsdElemg != NULL) {
							xsdElem = xsdElemg;
						} else
							xsdElem = getXSDElementDefinition (elem->name); 

	if (xsdElem == NULL) {
		cout << "\n Element Definition not found for XML element: " << elem->name; 
		popError(1);
	}
					if(debug>4) {
	xsdElem->print(); 
	cout << "\n-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ ";		}
	// STEP 1: Check the attributes: 
									// For each attribute of elem, try to retrieve the attribute def/ref within.
									// Then verify the value of that attribute. 
				for (int k=0; k<elem->attributes.size(); ++k) {
					xsdAttr = this->getXSDAttributeDefinition (elem->attributes[k]->name, xsdElem->xType); 
					if (xsdAttr == NULL) {
						// 09-Jul'07 Check if this attribute is xmlns:xsi OR xsi:noNamespaceSchemaLocation
						if (!xsdElem->checkOtherPossibleAttributes (elem->attributes[k]->name)) {
							sdd->attr = elem->attributes[k];  
							popError (2, " Attribute definition not found ");
						} 
					} else {
						if (xsdAttr != NULL) {
							sprintf (buf, "            %s,%s=> ", elem->name, elem->attributes[k]->name); if(debug>6)
							xsdAttr->print(buf);
						}
						if (xsdAttr->isReference) {
							xsdAttr = this->getXSDAttributeDefinition (elem->attributes[k]->name); 
						}
						sdd->attr = elem->attributes[k]; 
						xsdAttr->verifyValue(elem->attributes[k]->value, this); 
					}
				}
						
	// STEP 2: Check the content: 
		if (xsdElem->xType != NULL) {
			sdd->attr = NULL; sdd->eleM = elem;
			if (elem->content != NULL)
			xsdElem->xType->verifyValue (elem->content, 3, this); 
		}
				
	// STEP 3: Check the child elements: 	
																XSDElementDefinition	*chxsdElem; 
																	sdd->eleM = elem;
				for (int k=0; k<elem->childs.size(); ++k) {
					chxsdElem = this->getXSDElementDefinition (elem->childs[k]->name, xsdElem); 
					if (chxsdElem == NULL) {
						sprintf (buf, " Child Element [%s] has not been specified for %s ", elem->childs[k]->name,
																							elem->name);
						popError (4, buf);
					}
					if (chxsdElem != NULL) {
						sprintf (buf, "%s,%s   ", elem->name, elem->childs[k]->name);	if(debug>6)
						chxsdElem->print(buf);
					} 
								
					if (chxsdElem->isReference) {
						chxsdElem = this->getXSDElementDefinition (elem->childs[k]->name); 
						if (chxsdElem == NULL) {
							sprintf (buf, " Element [%s] referred to but not defined ", elem->childs[k]->name);
							popError (4, buf); 
						} else {
							sprintf (buf, "%s,%s   ", elem->name, elem->childs[k]->name); if(debug>6)
							chxsdElem->print(buf);
						}
					}
					this->verifyElementWithSchemaSpecs (elem->childs[k], chxsdElem);
				}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



XSDAttributeGroup*
XSDparser::getXSDAttributeGroup (char *gName) {
		for (int k=0; k<xsdAttributeGroupsV.size(); ++k) {
			if (!strcmp (xsdAttributeGroupsV[k]->name, gName) ) {
				return xsdAttributeGroupsV[k]; 
			}
		}
		return NULL; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



XSDElementGroup*
XSDparser::getXSDElementGroup (char *gName) {
		for (int k=0; k<xsdElementGroupsV.size(); ++k) {
			if (!strcmp (xsdElementGroupsV[k]->name, gName) ) {
				return xsdElementGroupsV[k]; 
			}
		}
		return NULL; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!




XSDAttributeDefinition*
XSDparser::getXSDAttributeDefinition (char *gName, XSDType *assignedType) {
		
		XSDType *withinType = assignedType;
		if (assignedType != NULL && assignedType->isReference) {
			withinType = getXSDType (assignedType->name);  if (debug>7)
					withinType->print("  ");
					if (withinType == NULL) {
							sprintf (buf, 
								" getXSDType() => XSDType [%s] referred to but not defined ", 
																				withinType->name); 
							popError (10, buf);
					}
					// Check if gElementName is mentioned in this type; 				
		}
		//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --
		if(withinType != NULL) {
			for (int i=0; i<withinType->attributesV.size(); ++i) {
				if (!strcmp (withinType->attributesV[i]->name, gName) ) {
					return withinType->attributesV[i]; 
				}
			}
																									if(debug>8)
			cout << "\n Also searching in attrGroupsV: " << withinType->attrGroupsV.size() << "  " << gName;
			for (int i=0; i<withinType->attrGroupsV.size(); ++i) {
														XSDAttributeGroup	*xsdAttrGrp; 
				if (withinType->attrGroupsV[i]->isReference) {
					xsdAttrGrp = this->getXSDAttributeGroup(withinType->attrGroupsV[i]->name);
					if (xsdAttrGrp == NULL) {
						sprintf (buf, " Attribute Group [%s] referred to but not defined ", 
																		withinType->attrGroupsV[i]->name); 
						popError (10, buf);
					}
				} else
					xsdAttrGrp = withinType->attrGroupsV[i];				if(debug>7)
		 										xsdAttrGrp->print(" ");	
				if (xsdAttrGrp->isGroupMember (gName) ) {
					return xsdAttrGrp->getGroupMember (gName); 
				}
			}
		}//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  -- 
		
		// If the given type is an extension of some other type, then check with that.............	
					
					
		// The given attribute definition could not be traced within the given type. 
		// Next trying for the exhaustive list: 
		for (int k=0; k<xsdAttributeDefsV.size(); ++k) {
			if (!strcmp (xsdAttributeDefsV[k]->name, gName) ) {
				return xsdAttributeDefsV[k]; 
			}
		}
		return NULL; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!







XSDElementDefinition*
XSDparser::getXSDElementDefinition (char *gElemName, XSDElementDefinition *withinElem) {
	
	if(withinElem != NULL) {
		if (withinElem->xType != NULL) {
			//cout << "\n Now trying out the two possibilities: ";
			XSDType *xType = withinElem->xType;  
			if (withinElem->xType->isReference) {
					xType = getXSDType (withinElem->xType->name);  if (debug>7)
					xType->print("  ");
					if (xType == NULL) {
							sprintf (buf, 
								" getXSDType() => XSDType [%s] referred to but not defined ", 
																				withinElem->xType->name); 
							popError (10, buf);
					}
					// Check if gElementName is mentioned in this type; 				
			}

			if (xType->nst != NULL) {
				for (int k=0; k<xType->nst->xLeafV.size(); ++k) {
					if (xType->nst->xLeafV[k]->xElem != NULL) {
						if (!strcmp(xType->nst->xLeafV[k]->xElem->name, gElemName))
							return 	xType->nst->xLeafV[k]->xElem; 
					} else 
					if (xType->nst->xLeafV[k]->xElemGrp != NULL) {
								XSDElementGroup	*xsdElemGrp = xType->nst->xLeafV[k]->xElemGrp;
						if (xsdElemGrp->isReference) {
							xsdElemGrp = getXSDElementGroup (xsdElemGrp->name); if(debug>7)
							xsdElemGrp->print(" ");
							if (xsdElemGrp == NULL) {
									sprintf (buf, 
									" getXSDElementDefinition() => Element Group [%s] referred to but not defined ", 
																						xsdElemGrp->name); 
									popError (10, buf);
							}
						} 
						if (xsdElemGrp->isGroupMember (gElemName) ) {
							return xsdElemGrp->getGroupMember (gElemName); 
						}
					}
				}
			} 
		}
	}
	
	for (int k=0; k<xsdElementDefsV.size(); ++k) {
		//cout << "\n\n Trying : "; xsdElementDefsV[k]->print(); 
		if (!strcmp (xsdElementDefsV[k]->name, gElemName)) {
			return xsdElementDefsV[k];
		}	
	}
	return NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!




XSDType*
XSDparser::getXSDType (char *gTypeName) {
			
	for (int k=0; k<xsdTypesV.size(); ++k) {
		if (!strcmp (xsdTypesV[k]->name, gTypeName)) {
			return xsdTypesV[k];
		}	
	}
	return NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


XSDparser::~XSDparser() {}
XSDparser::XSDparser() {
																schemaFileName 	=	NULL; 		
																xmlParser		=	NULL; 
																debug 			=  	0;	
		for (int i=0; i<40; ++i)
				xsdAllowedElementsV.push_back (new XSDAllowedElement);
				
	int	k=0;	
		xsdAllowedElementsV[k]->setName ("ROOT"); 
							xsdAllowedElementsV[k]->addChildName ("schema"); 
	k++;	
		xsdAllowedElementsV[k]->setName ("schema"); 
							xsdAllowedElementsV[k]->addChildName ("element"); 
							xsdAllowedElementsV[k]->addChildName ("attribute"); 
							xsdAllowedElementsV[k]->addChildName ("attributeGroup"); 
							xsdAllowedElementsV[k]->addChildName ("elementGroup"); 
							xsdAllowedElementsV[k]->addChildName ("annotation"); 
							xsdAllowedElementsV[k]->addChildName ("simpleType"); 
							xsdAllowedElementsV[k]->addChildName ("complexType"); 
								
										xsdAllowedElementsV[k]->addAttributeName ("xmlns");
										xsdAllowedElementsV[k]->addAttributeName ("xmlns:xs");
										xsdAllowedElementsV[k]->addAttributeName ("xmlns:xsd");
										xsdAllowedElementsV[k]->addAttributeName ("xmlns:hfp");
										xsdAllowedElementsV[k]->addAttributeName ("xml:lang");
										xsdAllowedElementsV[k]->addAttributeName ("targetNamespace");
										xsdAllowedElementsV[k]->addAttributeName ("blockDefault");
										xsdAllowedElementsV[k]->addAttributeName ("elementFormDefault");
	k++;	
		xsdAllowedElementsV[k]->setName ("element"); 
							xsdAllowedElementsV[k]->addChildName ("complexType"); 
							xsdAllowedElementsV[k]->addChildName ("simpleType"); 
										xsdAllowedElementsV[k]->addAttributeName ("name");
										xsdAllowedElementsV[k]->addAttributeName ("ref");
										xsdAllowedElementsV[k]->addAttributeName ("type");
										xsdAllowedElementsV[k]->addAttributeName ("minOccurs");
										xsdAllowedElementsV[k]->addAttributeName ("maxOccurs");
			// Different attributes may be relevant in different contexts, however we do not provide such checks. 
	k++;										
		xsdAllowedElementsV[k]->setName ("attribute"); 
							xsdAllowedElementsV[k]->addChildName ("simpleType"); 
										xsdAllowedElementsV[k]->addAttributeName ("name");
										xsdAllowedElementsV[k]->addAttributeName ("fixed");
										xsdAllowedElementsV[k]->addAttributeName ("type");
										xsdAllowedElementsV[k]->addAttributeName ("ref");
										xsdAllowedElementsV[k]->addAttributeName ("use");
	k++;										
		xsdAllowedElementsV[k]->setName ("elementGroup"); 
							xsdAllowedElementsV[k]->addChildName ("sequence"); 
										xsdAllowedElementsV[k]->addAttributeName ("name");
										xsdAllowedElementsV[k]->addAttributeName ("ref");
	k++;										
		xsdAllowedElementsV[k]->setName ("attributeGroup"); 
							xsdAllowedElementsV[k]->addChildName ("attribute"); 
										xsdAllowedElementsV[k]->addAttributeName ("name");
										xsdAllowedElementsV[k]->addAttributeName ("ref");
	k++;	
		xsdAllowedElementsV[k]->setName ("complexType"); 
							xsdAllowedElementsV[k]->addChildName ("sequence"); 
							xsdAllowedElementsV[k]->addChildName ("attribute"); 
							xsdAllowedElementsV[k]->addChildName ("attributeGroup"); 
							xsdAllowedElementsV[k]->addChildName ("complexContent"); 
										xsdAllowedElementsV[k]->addAttributeName ("name");
	k++;	
		xsdAllowedElementsV[k]->setName ("simpleType"); 
							xsdAllowedElementsV[k]->addChildName ("sequence"); 
							xsdAllowedElementsV[k]->addChildName ("annotation"); 
							xsdAllowedElementsV[k]->addChildName ("restriction"); 
							xsdAllowedElementsV[k]->addChildName ("list"); 
							xsdAllowedElementsV[k]->addChildName ("union"); 
										xsdAllowedElementsV[k]->addAttributeName ("name");
										xsdAllowedElementsV[k]->addAttributeName ("id");
	k++;	
		xsdAllowedElementsV[k]->setName ("sequence"); 
							xsdAllowedElementsV[k]->addChildName ("element"); 
							xsdAllowedElementsV[k]->addChildName ("elementGroup"); 
										xsdAllowedElementsV[k]->addAttributeName ("minOccurs");
										xsdAllowedElementsV[k]->addAttributeName ("maxOccurs");
	k++;	
		xsdAllowedElementsV[k]->setName ("union"); 
							xsdAllowedElementsV[k]->addChildName ("simpleType"); 
	k++;	
		xsdAllowedElementsV[k]->setName ("restriction"); 
										xsdAllowedElementsV[k]->addAttributeName ("base");
							xsdAllowedElementsV[k]->addChildName ("simpleType"); 
							xsdAllowedElementsV[k]->addChildName ("pattern"); 
							xsdAllowedElementsV[k]->addChildName ("minInclusive"); 
							xsdAllowedElementsV[k]->addChildName ("maxInclusive"); 
							xsdAllowedElementsV[k]->addChildName ("enumeration"); 
							xsdAllowedElementsV[k]->addChildName ("whiteSpace"); 
							xsdAllowedElementsV[k]->addChildName ("minLength"); 
							xsdAllowedElementsV[k]->addChildName ("fractionDigits"); 
	k++;	
		xsdAllowedElementsV[k]->setName ("complexContent"); 
							xsdAllowedElementsV[k]->addChildName ("extension"); 
	k++;	
		xsdAllowedElementsV[k]->setName ("extension"); 
										xsdAllowedElementsV[k]->addAttributeName ("base");
							xsdAllowedElementsV[k]->addChildName ("sequence"); 
							xsdAllowedElementsV[k]->addChildName ("attribute"); 
							xsdAllowedElementsV[k]->addChildName ("attributeGroup"); 
	k++;	
		xsdAllowedElementsV[k]->setName ("enumeration"); 
										xsdAllowedElementsV[k]->addAttributeName ("value");
	k++;	
		xsdAllowedElementsV[k]->setName ("minLength"); 
										xsdAllowedElementsV[k]->addAttributeName ("value");
										xsdAllowedElementsV[k]->addAttributeName ("id");
	k++;	
		xsdAllowedElementsV[k]->setName ("minInclusive"); 
										xsdAllowedElementsV[k]->addAttributeName ("value");
										xsdAllowedElementsV[k]->addAttributeName ("id");
	k++;	
		xsdAllowedElementsV[k]->setName ("maxInclusive"); 
										xsdAllowedElementsV[k]->addAttributeName ("value");
										xsdAllowedElementsV[k]->addAttributeName ("id");
	k++;	
		xsdAllowedElementsV[k]->setName ("annotation"); 
							xsdAllowedElementsV[k]->addChildName ("xs:documentation"); 
							xsdAllowedElementsV[k]->addChildName ("xs:appinfo"); 
	k++;	
		xsdAllowedElementsV[k]->setName ("documentation"); 
										xsdAllowedElementsV[k]->addAttributeName ("source");
	k++;	
		xsdAllowedElementsV[k]->setName ("whiteSpace"); 
										xsdAllowedElementsV[k]->addAttributeName ("value");
										xsdAllowedElementsV[k]->addAttributeName ("id");
	k++;	
		xsdAllowedElementsV[k]->setName ("pattern"); 
							xsdAllowedElementsV[k]->addChildName ("xs:annotation"); 
										xsdAllowedElementsV[k]->addAttributeName ("value");
										xsdAllowedElementsV[k]->addAttributeName ("id");
	k++;	
		xsdAllowedElementsV[k]->setName ("appinfo"); 
							xsdAllowedElementsV[k]->addChildName ("hasFacet"); 
							xsdAllowedElementsV[k]->addChildName ("hasProperty"); 
	k++;	
		xsdAllowedElementsV[k]->setName ("hasFacet"); 
							xsdAllowedElementsV[k]->addChildName ("hasProperty"); 
										xsdAllowedElementsV[k]->addAttributeName ("name");
	k++;	
		xsdAllowedElementsV[k]->setName ("hasProperty"); 
										xsdAllowedElementsV[k]->addAttributeName ("name");
										xsdAllowedElementsV[k]->addAttributeName ("value");
	k++;	
		xsdAllowedElementsV[k]->setName ("list"); 
										xsdAllowedElementsV[k]->addAttributeName ("itemType");
	k++;	
		xsdAllowedElementsV[k]->setName ("fractionDigits"); 
										xsdAllowedElementsV[k]->addAttributeName ("fixed");
										xsdAllowedElementsV[k]->addAttributeName ("value");
										xsdAllowedElementsV[k]->addAttributeName ("id");
											
	k++;	
		xsdAllowedElementsV[k]->setName ("attribute"); 
							xsdAllowedElementsV[k]->addChildName ("simpleType"); 
										xsdAllowedElementsV[k]->addAttributeName ("name");
										xsdAllowedElementsV[k]->addAttributeName ("fixed");
	k++;	
		xsdAllowedElementsV[k]->setName ("simpleType"); 
							xsdAllowedElementsV[k]->addChildName ("union"); 
							xsdAllowedElementsV[k]->addChildName ("restriction"); 
	k++;	
		xsdAllowedElementsV[k]->setName ("union"); 
							xsdAllowedElementsV[k]->addChildName ("simpleType"); 
	k++;	
		xsdAllowedElementsV[k]->setName ("restriction"); 
							xsdAllowedElementsV[k]->addChildName ("simpleType"); 
							xsdAllowedElementsV[k]->addChildName ("pattern"); 
							xsdAllowedElementsV[k]->addChildName ("minInclusive"); 
							xsdAllowedElementsV[k]->addChildName ("maxInclusive"); 
							xsdAllowedElementsV[k]->addChildName ("enumeration"); 
										xsdAllowedElementsV[k]->addAttributeName ("base");
	k++;	
		xsdAllowedElementsV[k]->setName ("minInclusive"); 
										xsdAllowedElementsV[k]->addAttributeName ("value");
	k++;	
		xsdAllowedElementsV[k]->setName ("maxInclusive"); 
										xsdAllowedElementsV[k]->addAttributeName ("value");
	k++;	
		xsdAllowedElementsV[k]->setName ("enumeration"); 
										xsdAllowedElementsV[k]->addAttributeName ("value");
	k++;	
		xsdAllowedElementsV[k]->setName ("pattern"); 
	k++;
										if (k > xsdAllowedElementsV.size()) {
												cout << "\n\n\t Error ........ Total number of allocated"
													<< " allowed elements should be " << k << " as against"
												    << " the current allocation of " << xsdAllowedElementsV.size();
												cout << "......... Exiting\n\n"; exit (0);	
										}
	int nSTokens = k;
	// --------------------- Fill-up the schemaConstructs with pointers to the child constructs -----------------
		for (int s=0; s<nSTokens; ++s) { 
			xsdAllowedElementsV[s]->myID = s;
																	if(debug>7)
			cout << "\n XSDparser() => Read xsdAllowedElement: " << xsdAllowedElementsV[s]->name;
			for (int c=0; c<xsdAllowedElementsV[s]->allowedChildsN.size(); ++c) {
				int j = getSchemaTokenIndex(xsdAllowedElementsV[s]->allowedChildsN[c]); 	
				if (j != -1) {
					xsdAllowedElementsV[s]->allowedChilds.push_back (xsdAllowedElementsV[j]); 
																if(debug>7)
					cout << " " << xsdAllowedElementsV[j]->name;   
				} else {
					cout << "\n ???????????? ERROR strange schema element ??????????????  [" 
													<< xsdAllowedElementsV[s]->allowedChildsN[c] << "]"; 
			   		cout << "\n Please check the structure of: [" << xsdAllowedElementsV[s]->name << "]";
					cout << "\n\n";	exit (0); 
				}
			}
		}
		
		if(debug>8)
		for (int s=0; s<nSTokens; ++s) { 
			xsdAllowedElementsV[s]->print(); 	
		}	
			
																	xsdSimpleDataTypesV.push_back("integer"); 
																	xsdSimpleDataTypesV.push_back("long"); 
																	xsdSimpleDataTypesV.push_back("positiveInteger"); 
																	xsdSimpleDataTypesV.push_back("NMTOKEN"); 
																	xsdSimpleDataTypesV.push_back(""); 
		//	for (int k=0; k<50; ++k) 	stid.push_back (k);						
		//	for (int k=0; k<10; ++k) 	dtid.push_back (k);						
																	//nDTokens = xsdSimpleDataTypesV.size(); 
			sdd = new SchemaDynamicStructures(); 
			xsdSimpleDataType = new XSDSimpleDataType(); 
			buf = new char[5000];
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!





void
XSDparser::checkSchemaStructure (XMLelement *xElem) {
																						if(debug>6)
		cout << "\n\t ------------------------ check-Schema-Structure () -------------------- ";  	
		// Search this schema element in the construct list 
		int	T = getSchemaTokenIndex (xElem->name);
			if (T != -1) {
				xsdAllowedElementsV[T]->checkSchemaElementStructure (xElem, this);
			}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



int	
XSDparser::getSchemaTokenIndex (char *tokName) {
																	int	nSTokens = xsdAllowedElementsV.size();
		for (int i=0; i<nSTokens; ++i) {
			//if (!strcmp (xsdAllowedElementsV[i]->name, tokName))
			if (xsdAllowedElementsV[i]->matchesElemName (tokName))
				return i;
		}
		return -1;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



XSDSimpleDataType::~XSDSimpleDataType() {}

XSDSimpleDataType::XSDSimpleDataType() {

}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

void
XSDSimpleDataType::print(char *indent) {
		
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

bool
XSDSimpleDataType::checkSimpleDataType (char *dataType, char *gValue, XSDparser *xsdParser) {
																				int	check = 0;
	if (!strcmp (dataType, "integer")) {
			check = isItTextOrNumber (gValue); 
			if (check == 1 || check == -1)  return true;
			else							return false; 
										
	} else if (!strcmp (dataType, "positiveInteger")) {
			check = isItTextOrNumber (gValue); 
			if (check == 1) return true;
			else			return false;

	} else if (!strcmp (dataType, "decimal")) {
			check = isItTextOrNumber (gValue); 
			if (check != 5) return true;
			else			return false;
	} else if (!strcmp (dataType, "string") || !strcmp (dataType, "NMTOKEN")) {
			check = isItTextOrNumber (gValue); 
			if (check == 5) return true;
			else			return false; 
	} else {
			cout << "\n\n ??????????? This is a strange data type [" << dataType << "]  for value: " << gValue; 
			cout << "\n\n"; exit (0);
	}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



int
XSDSimpleDataType::isItTextOrNumber (char *gValue) {
													// Returns  1: for only numbers
													// Returns	2: for numbers with decimal point
													// Returns	5: for text and possible numerals also. 
													bool	hasText = false;
													bool	hasNumerals = false, hasDecimal = false;
				for (int k=0,Z=strlen(gValue); k<Z; ++k) {
											if (k==0 &&  (gValue[k] == '-' || gValue[k] == '+')) continue;
					if (gValue[k] >= 48 && gValue[k] <= 57) {
						hasNumerals = true;
					} else if (gValue[k] == '.') {
						hasDecimal = true;
					} else {
						hasText = true; 
					}
				}
		if (hasNumerals && hasDecimal && !hasText) {
			if (gValue[0] == '-') return -2;
			return 2; 		
		}
		if (hasNumerals && !hasText) {
			if (gValue[0] == '-') return -1;
			return 1; 
		}
		if (hasText) return 5; 
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


bool
XSDAttributeDefinition::verifyValue (char *gValue, XSDparser *xsdParser) {
		if (fixed != NULL) {
			if (strcmp (gValue, fixed) ) {
				cout << "\n gValue/fixed: " << gValue << " <<<>>> " << fixed;
				xsdParser->popError(2, " Mismatched Fixed Value "); 
			}
			return true;
		}
		if (xType == NULL) {
			xsdParser->popError (2, " xType for this attribute NULL ");
		}
		if (xType->isReference) {
			xsdParser->sdd->xType = xsdParser->getXSDType (xType->name); 
			if (xsdParser->sdd->xType == NULL) {
				//cout << " Attribute,verifyValue()=> in-built data-type "; 
				//cout << "\n XSDAttributeDefinition => verifyValue() => This must be an in-built data-type "; 
				strcpy (xsdParser->buf, xType->name); 
				xsdParser->removeNameSpaceQualifier (xsdParser->buf); 
				return xsdParser->xsdSimpleDataType->checkSimpleDataType(xsdParser->buf, gValue);   
				//xsdParser->popError (2, " xType referred to but not defined ");
			}
		} else
			xsdParser->sdd->xType = xType;
		
		XSDType		*myType = xsdParser->sdd->xType;
					myType->verifyValue (gValue, 2, xsdParser); 
		return true;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_





bool
XSDType::verifyValue (char *gValue, int msgCode, XSDparser *xsdParser, bool dontExit) {
	// Check for restriction or nested structure. 	
	if (xRestriction != NULL) {
			return xRestriction->verifyValue (gValue, msgCode, xsdParser, dontExit); 
	}
																		dontExit = true;
	if (nst != NULL) {
		if (nst->isUnion) {
			// Any one of the leaf can be satisfied
			for (int k=0; k<nst->xLeafV.size(); ++k) {
				if (nst->xLeafV[k]->xType == NULL) { // This is Must!
					xsdParser->sdd->xLeaf = nst->xLeafV[k]; 
					xsdParser->popError (10, " The components for XSDType HAVE TO BE an XSDType... check schema "); 
				}
				if (nst->xLeafV[k]->xType->verifyValue (gValue, msgCode, xsdParser, dontExit))  return true;
			}
			xsdParser->popError (msgCode, 
								" NONE of isUnion options of complex type have conformed with value/content "); 
			return false;
		}	
	}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
		
	
bool
XSDRestriction::verifyValue (char *gValue, int msgCode, XSDparser *xsdParser, bool dontExit) {
																					if(xsdParser->debug>6) {
		cout << "\n XSDRestriction verifyValue () " << gValue;	this->print("\t\t\t"); }
		
		if (enumeration.size() > 0) {	// The base is not so effective in validation. 
			for (int k=0; k<enumeration.size(); ++k) {
				if (!strcmp (enumeration[k], gValue) ) {
					return true;
				}
			}
			if (!dontExit)
			xsdParser->popError(msgCode, " The given Value has not been enumerated ");
			return false; 
		}
		// Step 1: Now do the type checking of the data -------------------------
		if (xsdParser->matchesElementNameOnly (base, "string") || xsdParser->matchesElementNameOnly (base,"NMTOKEN")) {
			if (!xsdParser->xsdSimpleDataType->checkSimpleDataType("string", gValue, xsdParser) ) {
				if (!dontExit)
				xsdParser->popError (msgCode, " Expected a STRING data type !! "); 
				return false;
			}
							
		} else if (xsdParser->matchesElementNameOnly (base, "integer") ) {
			if (!xsdParser->xsdSimpleDataType->checkSimpleDataType("integer", gValue, xsdParser) ) {
				if (!dontExit)
				xsdParser->popError (msgCode, " Expected a INTEGER data type !! "); 
				return false;
			}
				
		} else if (xsdParser->matchesElementNameOnly (base, "positiveInteger") ) {
			if (!xsdParser->xsdSimpleDataType->checkSimpleDataType("positiveInteger", gValue, xsdParser) ) {
				if (!dontExit)
				xsdParser->popError (msgCode, " Expected a POSITIVE INTEGER data type !! "); 
				return false;
			}

			
		} else if (xsdParser->matchesElementNameOnly (base, "decimal") ) {
			if (!xsdParser->xsdSimpleDataType->checkSimpleDataType("decimal", gValue, xsdParser) ) {
				if (!dontExit)
				xsdParser->popError (msgCode, " Expected a DECIMAL data type !! "); 
				return false;
			}
		}
			
		// Step 2: Now check if the data is in the required range ---------------------------
		if (howSpecified == 1 || howSpecified == 2 || howSpecified == 3) {
																	float numericValue;
			sscanf (gValue, "%f", &numericValue); 	
			if ((numericValue >= minInclusive && numericValue <= maxInclusive) ||
				fabs(numericValue-minInclusive) < 0.00001 ||  fabs(numericValue-maxInclusive) < 0.00001 ) 
									return true;
			else {
				if (!dontExit)
				xsdParser->popError (msgCode, " Number not in specified range "); 
				return false; 
			}
		}	
		
			
		return true;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
		
			
		
void
XSDparser::popError (int errorCode, char *msg) {
							
	cout << "\n\n__________________________________________________\n\t Error: Schema Validation FAILED "; 
	if (msg != NULL) cout << "\n\t\t >>>" << msg << "<<< "; 	

	if (errorCode == 1) {
		cout << "\n\t 1. Element [" << sdd->eleM->name << "] was not found in schema";
		cout << "\n\t 1. Element"; sdd->eleM->printAttributes(); cout << " ???????????????????? "; 
	} else if (errorCode == 2) {
		cout << "\n\t 2. Element [" << sdd->eleM->name << "] has got a invalid attribute/value ";
		cout << "\n\t 2. Attribute"; sdd->attr->print(); cout << " ???????????????????? "; 
	} else if (errorCode == 3) {
		cout << "\n\t 3. Element [" << sdd->eleM->name << "] has got a invalid content ";
		cout << "\n\t 3. Content ["; if (sdd->eleM->content != NULL) cout << sdd->eleM->content;
	   												cout << "]  ???????????????????? "; 
			cout << "\n >>>>>>>>>>>>>>Schema definition is: ---------";
			if (sdd->xsdElem != NULL)	sdd->xsdElem->print("  ");
	} else if (errorCode == 4) {
			cout << "\n\t 4. Wrong child element... ["; if (msg != NULL) cout << msg; 
			cout << "]\n\t\t for element-tag ";  sdd->eleM->print();  
			cout << "\n >>>>>>>>>>>>>>Schema definition is: ---------";
			if (sdd->xsdElem != NULL)	sdd->xsdElem->print("  ");
																				// [" << sdd->eleM-> << "]"; 
	} else if (errorCode == 5) {
	} else if (errorCode == 31) {
																				// [" << sdd->eleM-> << "]"; 
	} else if (errorCode == 10) { 
			cout << "\n  10. Printing the schema parser state below: ";
			if (sdd->eleM != NULL) {	cout << "\n"; sdd->eleM->print(); }
			if (sdd->xLeaf != NULL) {	cout << "\n"; sdd->xLeaf->print(" "); }
			if (sdd->xsdElem != NULL) {cout << "\n >>>>>>>>>>>>>>Schema definition is: ---------";
																			sdd->xsdElem->print(" "); }
			if (sdd->xsdAttr != NULL) {	cout << "\n"; sdd->xsdAttr->print(" "); }
	}
	if (sdd->eleM != NULL) {
		cout << "\n\n\t Getting position of element: "; sdd->eleM->printAttributes(); 
															int		lineNumber;
		lineNumber =  calculateLineNumber (sdd->fileNameInWhichErrorOccurred, sdd->eleM->filePointer); 
		char *onlyFileName = NULL;
		if (sdd->fileNameInWhichErrorOccurred != NULL) {
			onlyFileName = new char[strlen(sdd->fileNameInWhichErrorOccurred)+1];
			strcpy (onlyFileName, sdd->fileNameInWhichErrorOccurred);
				int	 bg;
			for (bg=strlen(onlyFileName); bg>=0; --bg) {
				if (onlyFileName[bg] == '/') {
					break;
				}
			}
			for (int k=bg+1; k<=strlen(onlyFileName); ++k) 
				onlyFileName[k-bg-1] = onlyFileName[k];
		}

		cout << "\n Line:"<< lineNumber << " >> Check  input data file: [" << onlyFileName 
																			<< "] around line number: " << lineNumber;
		cout << "\n Line:"<< lineNumber << " >> Check  input data file: [" << onlyFileName 
																			<< "] around line number: " << lineNumber;
	}
	cout <<"\n--------------------------------------------------\n\n\n" <<  flush; 
		assert (1==2); 
		
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_





int
XSDparser::calculateLineNumber (char *fileName, long int filePointer) { 
								cout << "  File Pointer:  " << filePointer;
																					//filePointer += 10;
		long int 		requestedBytes, bytesToRead = filePointer;
																							fstream fin;
										fin.open (fileName,ios::in|ios::binary);
				if (!fin.good()) {	
					cout << "\n ,,,,,,,,,,,XSDparser::Unable to read the file: " << fileName << "\n\n"; exit (0);
				}

											
		fin.seekg (0, ios::end);
		long int 		totalFileSize = fin.tellg(), nowAt, bytesLeft;
		fin.seekg (0, ios::beg);
		char ch;
																int 	lineCount = 1;
																int		uc = 0, _bufSize = 29;			
				char *dataBuf 	= 	new char[_bufSize];
		fin.clear(); 
																bool	reachedRequiredLine = false; 
		while ( ! fin.eof() && !reachedRequiredLine) {
					nowAt = fin.tellp(); 
					requestedBytes = ((bytesLeft=totalFileSize-nowAt) > _bufSize) ? 
																		_bufSize : bytesLeft;
					
															//cout<< "\n Requested Bytes: " << requestedBytes<<flush;
															if (requestedBytes == 0) break;
							
					fin.read ((char*)dataBuf, requestedBytes);
					for (int i=0; i<requestedBytes; ++i) {
						if (dataBuf[i] == '\n') lineCount ++;
						if (nowAt+i >= filePointer) {reachedRequiredLine=true; break; }
					}
								// dataBuf[requestedBytes] = '\0';
								// cout <<"\n--------------------- READ DATABUF: " << "[" << dataBuf <<"]";
		}
		// cout << "\n Determined lineCount: " << lineCount;
		return lineCount;

		
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_





IncompleteWork::~IncompleteWork () {delete [] workName;}
IncompleteWork::IncompleteWork () {}

IncompleteWork::IncompleteWork (XMLelement *xelem, XSDType *xType, char *workName) {
	this->xelem = xelem;
	this->xType = xType;
	this->workName = new char[strlen(workName)+1];
	strcpy (this->workName, workName);
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


void
IncompleteWork::print() {

	if (workName != NULL)  cout <<"  w_" << workName; 
	if (xType != NULL) if (xType->name != NULL) cout << " t_" << xType->name;
	if (xelem != NULL) if (xelem->name != NULL) cout << " e_" << xelem->name;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_




