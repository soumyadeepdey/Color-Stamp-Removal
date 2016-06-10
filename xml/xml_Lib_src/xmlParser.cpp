//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Program Name : xmlParser.cpp
// 
// Project :  		Video Object Analysis
// Author : 		Gaurav Harit (PhD EE-2001)
// Creation Date : 	Sep 17  -2005.  Rights Reserved
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*

#include "xmlParser.h"




XMLattribute::XMLattribute () { name = NULL; value = NULL; }
XMLelement::XMLelement () { name = NULL; content = NULL; parent = NULL; filePointer = -1; myID = -1;}

XMLattribute::~XMLattribute () { if(name != NULL) delete [] name; if(value != NULL) delete [] value; }
XMLelement::~XMLelement () {
	//cout << " DESTROYING Xmlelement ";
	if(name != NULL) delete [] name; if(content!= NULL) delete [] content; 
	for (int k=0; k<attributes.size(); ++k) 	delete attributes[k];	attributes.clear();
	for (int i=0; i<childs.size(); ++i) 		delete childs[i];		childs.clear();
}



void
XMLelement::setContent (vector<char *>	& contentArray)  {
	int	len = 0;
	for (int k=0; k<contentArray.size(); ++k) {
		len += (strlen(contentArray[k])+1); 	len ++;
	}
	len ++;
	if (content != NULL)	delete [] content;
	content = new char[len+1];
	strcpy (content, "");
	for (int k=0; k<contentArray.size(); ++k) {
		strcat (content, contentArray[k]);	
		if (k != contentArray.size()-1)
				strcat (content, " ");
	}
	cout << " CONTENT: " << content;
	contentArray.clear();
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
	
void
XMLelement::setName (char *n) {
	if (name != NULL)	delete [] name;
	name = new char[strlen(n)+4];			strcpy (name, n);	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


void
XMLattribute::setName (char *n) {
	if (name != NULL)	delete [] name;
	name = new char[strlen(n)+4];			strcpy (name, n);	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


void
XMLattribute::setValue (char *v) {
	if (value != NULL)	delete [] value;
	value = new char[strlen(v)+4];			strcpy (value, v);	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

void
XMLattribute::print() {
										if (this == NULL) return;
	cout << " [";
	if (name != NULL) cout << name; cout << "<=>";
	if (value != NULL) cout << value;
	cout << "]";
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

void
XMLelement::printAttributes () {
													if (this == NULL) return;
	cout << " [" << name << "->";
 		
	if (attributes.size() > 0) {
		for (int k=0; k<attributes.size(); ++k) {
			if (attributes[k]->name != NULL && attributes[k]->value != NULL) {
				cout <<" " << attributes[k]->name  <<"="<< attributes[k]->value; 
				if (k != attributes.size()-1) cout << ",";
			}
			else cout << "\n Error: NULL attributes encountered !! ";
		}
		//cout << "]";
	}
	cout << "]";
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_




void
XMLelement::print (int detail) {
													if (this == NULL) return;
	char 	*buf = new char[100];
	sprintf (buf, "[%s]", name);
	cout << "\n  XMLnode: " <<setiosflags(ios::fixed) <<setiosflags(ios::left)<<setw(30) << buf << " ";	
	if (content != NULL)	cout << "  Content: [" << content << "]";
	//if (content == NULL) 	cout << " Nxxxxxxxxxxxxxxxxxxxoooooo Content ";
	if (attributes.size() > 0) {
		//cout << "\n\t\t\t\t Attributes: [";
		for (int k=0; k<attributes.size(); ++k) {
			if (attributes[k]->name != NULL && attributes[k]->value != NULL)
				cout <<"\n\t\t\t\t\t " << attributes[k]->name  <<" = "<< attributes[k]->value; 
			else cout << "\n Error: NULL attributes encountered !! ";
		}
		//cout << "]";
	}
	if (parent != NULL) {
		cout << "\n\t\t\t\t  Parent: [";
			if (parent->name != NULL) cout << parent->name; 
			else cout << "NoName";
		cout << "]";
	}
	if (childs.size() > 0) {
		cout << "\n\t\t\t\t  Child: [";
		for (int k=0; k<childs.size(); ++k) {
			if (childs[k]->name != NULL) cout << childs[k]->name; 
			else cout << "NoName";
			if(k!=childs.size()-1)cout << ", ";}
		cout << "]";
	}
	if (detail) {
		for (int k=0; k<childs.size(); ++k) 	childs[k]->print(1);
	}
	delete [] buf;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


char *
XMLelement::getAttributeValue (char *name) {
	for (int k=0; k<attributes.size(); ++k) {
		if (!strcmp (attributes[k]->name, name))
			return attributes[k]->value;
	}
	return NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

bool
XMLelement::hasAttributeValue (char *name, char *value) {
	for (int k=0; k<attributes.size(); ++k) {
		if (!strcmp (attributes[k]->name, name))
		if (!strcmp (attributes[k]->value, value))
			return true;
	}
	return false;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



XMLattribute*
XMLelement::getAttributeByValue (char *value) {
	for (int k=0; k<attributes.size(); ++k) {
		if (!strcmp (attributes[k]->value, value))
			return attributes[k];
	}
	return NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


bool
XMLelement::getAttributeValue (char *name, float & value) {
	for (int k=0; k<attributes.size(); ++k) {
		if (!strcmp (attributes[k]->name, name)) {
			sscanf (attributes[k]->value, "%f", &value);
			return true;
		}
	}
	return false;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


bool
XMLelement::getAttributeValue (char *name, int & value) {
	for (int k=0; k<attributes.size(); ++k) {
		if (!strcmp (attributes[k]->name, name)) {
			sscanf (attributes[k]->value, "%d", &value);
			return true;
		}
	}
	return false;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



XMLattribute*
XMLelement::getAttribute (int count) {
		if (attributes.size() > count) return attributes[count];
	return NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_




XMLelement*
XMLelement::getSibling (int count) {

	if (parent != NULL) {
			if (count < parent->childs.size()) {
				return parent->childs[count];
			}
	}	
			return NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
	




XMLelement*
XMLelement::getChild (char *name) {

	if (name != NULL) {
		for (int k=0; k<childs.size(); ++k) {
			if (!strcmp (childs[k]->name, name)) {
								// Start-Reset a counter for this child
					for (int c=0; c<=counterNames.size(); ++c) {
						if (c == counterNames.size()) {
							counterNames.push_back (childs[k]->name);
							counters.push_back (1); break;
						}
						if (!strcmp (counterNames[c], name)) {
							counters[c] = 1; break;
						}
					}
				return childs[k];
			}
		}
	} else {
		childCounter = 0;
		if (childCounter < childs.size()) {
			return childs[childCounter];
		}
	}	
			return NULL;
	/*	
	XMLelement	*myChild;
	for (int k=0; k<childs.size(); ++k) {
		myChild = childs[k]->getChild (name);
		if (myChild != NULL)
					return myChild;
	}
	return NULL;*/
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
	


XMLelement*
XMLelement::getChild (char *name, int num) {

	int 	myNumber = -1;
	if (name != NULL) {
		for (int k=0; k<childs.size(); ++k) {
			if (!strcmp (childs[k]->name, name)) {
				myNumber ++;
				if (myNumber == num)
					return childs[k];
			}
		}
	} else {
		if (num < childs.size()) {
			return childs[num];
		}
	}	
		return NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
	
XMLelement*
XMLelement::getChild (int num) {

		if (num < childs.size()) {
			return childs[num];
		}
		return NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
	



XMLelement*
XMLelement::getNextChild (char *name) {
	int		myNumber = -1;
	bool	skip = false;
	if (name != NULL) {
		for (int k=0; k<childs.size(); ++k) {
			if (!strcmp (childs[k]->name, name)) {
				myNumber++;	skip = false;
						for (int c=0; c<=counterNames.size(); ++c) {
							if (c == counterNames.size()) {
								counterNames.push_back (childs[k]->name);
								counters.push_back (1); break;
							}
							if (!strcmp (counterNames[c], name)) {
								if (myNumber == counters[c]) {
									counters[c] ++; // returning 
									break;
								} else
									skip = true;
							}
						}
				if (skip == true) continue;
				return childs[k];
			}
		}
	} else {
		childCounter ++;
		if (childCounter < childs.size()) {
			return childs[childCounter];
		}
	}
	return NULL;	// All children of this name have been returned.
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
	





//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
void
XMLelement::dumpInFile (XMLparser	*parser, char *indent, int level) {
	
	fstream		&fout = parser->fout;
	//this->print();getchar();		
	strcpy (indent, "");
	for (int i=0; i<level; ++i)
			strcat (indent, "\t");
	
	if (name != NULL) {
		
		if (level > 0)		fout <<"\n"	 << indent << "<" << name;
		else 				fout <<"\n\n"<< indent << "<" << name;

		if (attributes.size() > 0) {	
			for (int k=0; k<attributes.size(); ++k) {
				fout <<"  "<< attributes[k]->name << "=\"" << attributes[k]->value << "\"";
			}
		}
		
		if (content != NULL) {
			fout << ">";
			if (strcmp (content, ""))
			fout <<"\n\t" << indent << content;
		}
		
		if (childs.size() > 0) {
			if (content == NULL) fout << " >";
			for (int k=0; k<childs.size(); ++k)
					childs[k]->dumpInFile (parser, indent, level+1);
		}
			strcpy (indent, "");
			for (int i=0; i<level; ++i)
				strcat (indent, "\t");
		
		if (content == NULL && childs.size() == 0)
			fout << "/>";
		else
			fout << "\n" << indent << "</" << name << ">";
		
	}		
	if (level == 0)
	fout 
	<< "\n <!-- -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* -->";

}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
	
void
XMLparser::dumpInFile (char *outFileName) {
	
	fout.close(); fout.clear();
	
	fout.open(outFileName, ios::out | ios::binary);			assert (fout.good());
	cout << "\n Dumping XML-elements to file: " << outFileName;
	
	char *header = new char[100];
	strcpy (header, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	
	fout.write (header, strlen(header)*sizeof(char));
	
	char 	*indent = new char[1000];	// For very very deep nesting,
	int		level = 0; 					// this memory allocation will be insufficient
	
	for (int k=0; k<elementList.size(); ++k)
		elementList[k]->dumpInFile (this, indent, level);
			if (this->fileName == NULL) {
				this->fileName = new char[strlen(outFileName)+10]; 						
				strcpy (this->fileName, outFileName); 
			}
	delete [] indent;
	delete [] header;
	
	fout.close();
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
void
XMLparser::writeComment (char *buf) {
														assert (fout.good());
	fout << "\n <!-- " << buf << " -->";
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_	
	
XMLelement*
XMLparser::makeXMLelement (char *name) {
		XMLelement	*bel = new XMLelement();
		bel->setName (name);
		return bel;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	

void
XMLelement::addChildElement (XMLelement *child) {
	childs.push_back (child);	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



XMLelement*
XMLelement::makeChildElement (char *name) {
			
		XMLelement	*bel = new XMLelement();
		bel->setName (name);
		childs.push_back (bel);
		return bel;
		
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



void
XMLelement::setChildElement (XMLelement	*bel) {
		childs.push_back (bel);
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_




void
XMLelement::setAttribute (char *name, char *value) {  
	// First check if the attribute already exists. If yes then update it.
	
	for (int k=0; k<attributes.size(); ++k) {
		if (attributes[k] != NULL) 
		//if (!strcmp (attributes[k], name)) {
		if (!strcmp (attributes[k]->name, name)) {
			attributes[k]->setValue(value);
			return; 
		}
	}

		attributes.push_back (new XMLattribute);
		attributes.back()->setName (name);
		attributes.back()->setValue (value);
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


void
XMLelement::reset (bool alsoChildren) {
	if (name != NULL)		delete [] name;
	if (content != NULL) 	delete [] content;
			if (alsoChildren)
			for (int k=0; k<childs.size(); ++k)		delete childs[k];
	for (int k=0; k<attributes.size(); ++k) delete attributes[k];
	counterNames.clear(); counters.clear();	childCounter = 0;
	name = NULL; content = NULL; childs.clear(); attributes.clear(); filePointer = -1;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	

XMLelement*
XMLparser::getElementFromPool () {
	XMLelement	*born;
	if (!poolElements.empty()) {
		born = poolElements.front(); poolElements.pop();
						usedElements.push (born);
		return born;
	}
	born = new XMLelement();	
	usedElements.push (born);	return born;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

	
void
XMLparser::fillBackElementPool () {
	XMLelement	*used;
	while (!usedElements.empty()) {
			used = usedElements.front(); usedElements.pop();
			used->reset (false);
			poolElements.push (used);
	}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_
	
	
	
void
XMLparser::test () {
		setOutputFile ("myIndia.tex");
		XMLelement	*expElement = makeXMLelement ("JaiShreeRam");
				
			expElement->setContent ("Its too much of content... I cant bear it");
			expElement->setAttribute ("Variable1", "valueNone");
			expElement->setAttribute ("Variable2", "valueNone");
			expElement->setAttribute ("Variable3", "valueNone");
		XMLelement *c1 = expElement->makeChildElement ("OnlyChild");
		XMLelement *c2 = expElement->makeChildElement ("SecondChild");
			c1->setAttribute ("Hero1", "2");
			c2->setAttribute ("Hero2", "4");
			c1->makeChildElement ("GrandChild11");
			c1->addContent ("My Dear");
			c1->addContent ("  Gaurav");
			c1->addContent ("  Gaurav");
			c1->addContent ("  Gaurav");
			c1->addContent ("  Gaurav");
			c1->addContent ("  Gaurav");
			c1->addContent ("  Gaurav");
			c1->addContent ("  Gaurav");
			c1->makeChildElement ("GrandChild12");
			c2->makeChildElement ("GrandChild21");
			c2->makeChildElement ("GrandChild22");
			char 	*indent = new char[1000];
			int		level = 0;
			expElement->dumpInFile (this, indent, level);
			fout.close();
			delete [] indent;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

void
XMLparser::setOutputFile (char *fileName) {
		fout.close(); fout.clear(); 
		fout.open (fileName, ios::out);  
		if (!fout.good()) {
			cout << "\n\n\t ???? Some problem in opening the output file: [" << fileName << "]"; 
			cout << "\n\t\t Check that the directory/permissions exist... \n\n"; exit (0);
		}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
void
XMLparser::makeXMLgraphicalStructure (vector<char*>	& tokens) {
	
	
	stack<XMLelement*>		elmStack;
	XMLelement				*elm;
	XMLattribute			*attr;
	bool					readContent = false, readNextContent = false;
	vector<char*>			contentArray;

	for (int T=0; T<tokens.size(); ++T) {
		//cout << "\n For Token: " << tokens[T];
		
		if (!strcmp(tokens[T],"<") ) {
											assert (T < tokens.size()-1);
					elm = new XMLelement();	elm->setName (tokens[T+1]);
					if (!elmStack.empty())	elmStack.top()->childs.push_back (elm);
					else
							elementList.push_back (elm);
					elmStack.push (elm);
					//cout << " Pushed in: " << elmStack.top()->name;
					readNextContent = false;			T++;
					
		} else if (!strcmp(tokens[T],"</") ) {
					//cout << " Popped out: " << elmStack.top()->name;
					//-+-+-+-+-+-+
					if (elmStack.empty() || strcmp(elmStack.top()->name, tokens[T+1])) {
							cout << "\n\n ---------------------------------------- "; 
								cout << "\n\t Mis-Matched Tag in file [" << fileName << 
								"]  on/before line Number: " << lineNumbers[T];
							while (!elmStack.empty()) {
								cout << "\n\t\t STACK: " << elmStack.top()->name;	elmStack.pop();
							}
							cout << "\n\n"; exit (0);
					}
					//-+-+-+-+-+-+
					elm = elmStack.top();
					elmStack.pop();					
					T++;
					readNextContent = false;
			
		} else if (!strcmp(tokens[T],">") ) {
												readNextContent = true; 
		} else if (!strcmp(tokens[T],"/>") ) {
					//cout << " Popped out: " << elmStack.top()->name;
					readNextContent = false;
					elmStack.pop ();	
		} else if (!strcmp(tokens[T],"=") )  {
					attr = new XMLattribute ();	
					attr->setName (tokens[T-1]);
					attr->setValue (tokens[T+1]);	T++;
					elmStack.top()->attributes.push_back (attr);
									//elmStack.top()->print();
					readNextContent = false;
		}
		
		if (readContent && readNextContent){ contentArray.push_back (tokens[T]); }
		
		
		if (readNextContent) {	readContent = true;}
		else if(readContent) {	readContent = false;
								if (contentArray.size() > 0) {
									elm->setContent (contentArray);
								}	
		}								
		
	}// For all tokens....................................
			
		if (!elmStack.empty()) {
					cout << "\n\n ---------------------------------------- ";
					cout << "\n\t Mis-Matched Tag in file [" << fileName << 
							"]  on/before line Number: " << lineNumbers.back();
			while (!elmStack.empty()) {
					cout << "\n\t\t STACK: " << elmStack.top()->name;	elmStack.pop();
			}
			cout << "\n\n"; exit (0);
		}

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	for (int T=0; T<tokens.size(); ++T) {
		delete []  tokens[T];
	}
	tokens.clear();	lineNumbers.clear();
	
	cout << "\n\n ++++++++++++++++++++++++++++++++++++++\n Elements Read from XML document: \n";
	for (int k=0; k<elementList.size(); ++k) {
		elementList[k]->print();
	}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!




void
XMLparser::reset() {
	for (int T=0; T<tokens.size(); ++T) {
		if (tokens[T] != NULL)
			delete  [] tokens[T];
	}
								tokens.clear();	lineNumbers.clear();
	for (int k=0; k<elementList.size(); ++k)
		if (elementList[k] != NULL) delete elementList[k];

	elementList.clear();
	if (textLine != NULL)	delete [] textLine;		textLine = NULL;
	if (firstWord != NULL)	delete [] firstWord;	firstWord = NULL;
	if (unitChars != NULL)	delete [] unitChars;	MAXCHARS = 1; unitChars = new char[MAXCHARS];
	  //if (fin.good())	fin.close(); 
	  	fin.close(); 		fin.clear(); 
	  { fout.close(); }		fout.clear();
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	








//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
void
XMLparser::readDocument (char *fileName) {
	
								this->reset();	
	this->fileName = fileName;		
	fstream 	fin;
				fin.open (fileName, ios::in);		assert (fin.good());
			
	char	ch, *word;
				if (textLine == NULL) 	textLine 	= 	new char[1000];
				if (firstWord == NULL) 	firstWord 	= 	new char[1000];
	
	// vector<char>	unitChars;	unitChars.resize(1000);
	int		 uc = 0;// MAXCHARS=1;
	//char	*unitChars = new char[MAXCHARS];
	
	int			cLineNum = 0;
	// MAKE all the tokens by completely parsing the file:
				
		while (!fin.eof()) {
									
			fin.getline (textLine, 300);		assert (strlen(textLine) < 299);
			sscanf (textLine, "%s", firstWord);		//cout << "\n firstWord: " << firstWord;
			cLineNum ++;
			if (firstWord[0] == '%' || strlen(textLine) < 2) { continue; }	
			
			//cout << "\n " << textLine;
			// TOKENIZE		< > </	/>	= 	
			int		lineLength = strlen (textLine);
			int		initialNumberOfTokens = tokens.size();
			
			for (int k=0; k<lineLength; ++k) {
				
					//unitChars.push_back (textLine[k]);
				if (textLine[k] == '<') {	
					//if (unitChars.size() > 0)	
					if (uc > 0)	
						tokens.push_back (makeString(unitChars, uc));	
					//	tokens.push_back (new char[unitChars.size()+23]);	
					//if (unitChars.size() > 0)
					//cout << "\n  GETSTRING: " << makeString(unitChars);
					if (k != lineLength-1 && textLine[k+1] == '/') {	
						word = new char[5]; strcpy (word, "</");
						tokens.push_back (word);	k++;
					} else {
						word = new char[4]; strcpy (word, "<");
						tokens.push_back (word);
					}
					
				} else if (textLine[k] == '=') {
					//if (unitChars.size() > 0)	
					if (uc > 0)	
						tokens.push_back (makeString(unitChars, uc));	
					word = new char[4]; strcpy (word, "=");
					tokens.push_back (word);
					
				} else if (textLine[k] == '/') {
					if (k != lineLength-1 && textLine[k+1] == '>') {	
						//if (unitChars.size() > 0)	
						if (uc > 0)	
							tokens.push_back (makeString(unitChars, uc));	
						word = new char[5]; strcpy (word, "/>");
						tokens.push_back (word);	k++;
					} else {
						//unitChars.push_back (textLine[k]);
						unitChars[uc++] = textLine[k];	
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
					}
				} else if (textLine[k] == '>') {	
					//if (unitChars.size() > 0)	
					if (uc > 0)	
						tokens.push_back (makeString(unitChars, uc));	
					word = new char[4]; strcpy (word, ">");
					tokens.push_back (word);

				} else if (textLine[k] == ' ' || textLine[k] == '\t') {
					//if (unitChars.size() > 0)
					if (uc > 0)
						tokens.push_back (makeString(unitChars, uc));	
				} else {
					//cout << " " << textLine[k];
					if (textLine[k] != '\"')
						unitChars[uc++] = textLine[k];
						//unitChars.push_back (textLine[k]);
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
				
				}	
					
			}// For each char in the line: 	
			
			for (int T=initialNumberOfTokens; T < tokens.size(); ++T) {
					lineNumbers.push_back (cLineNum);
			}		
		}//--------------------------------------------------------------
			
	
		//cout << "\n\n";
		
		//for (int k=0; k<tokens.size(); ++k) {
		//	cout << "\n\t\t : " << tokens[k];
		//}
		
		delete [] textLine; delete [] firstWord; 	delete [] unitChars;
		textLine = NULL; firstWord = NULL; unitChars = NULL;
		
		
		makeXMLgraphicalStructure (tokens);
			
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
	
	


char *
XMLparser::makeString (vector<char> & unitChars) {
	
	char 	*bug = new char[unitChars.size()+1];
	int		k = 0;
		
			for (k=0; k<unitChars.size(); ++k)
							bug[k] = unitChars[k];
		bug[k] = '\0';	
		unitChars.clear();	
		return bug;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



char *
XMLparser::makeString (char* & unitChars, int & uc) {
	/*	
	int	skip = 0;
					for (int i=0; i<uc; ++i) {
						if (unitChars[i] == ' ' || unitChars[i] == '\t' || unitChars[i] == '\n') {
							skip ++;
							continue;
						}
						break;
					}
	if (skip == uc)		return NULL;
	*/				
	char 	*bug = new char[uc+1];
	int		k = 0;	//skip
			for (k=0; k<uc; ++k)
							bug[k] = unitChars[k];
		bug[k] = '\0';							/*	
											if (uc < 3) {
													cout << "\n  CONTENT  [" << bug <<"]";
													getchar();
											}	*/
		uc = 0;
		return bug;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!





XMLparser::XMLparser () {
		fileName = NULL; MAXCHARS=1; unitChars = new char[MAXCHARS];
		firstWord = NULL; textLine = NULL;		xsdParser = NULL;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
void
XMLparser::print() {
	cout << "\n\n ----------- xmlParser----printing [" << fileName << "]------["
														<< elementList.size() << "] Elements";
		for (int k=0; k<elementList.size(); ++k) {
						elementList[k]->print(1);
		}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!



bool
XMLparser::shortHandReadRootElements (char *fileName) {
								this->reset();	
	this->fileName = fileName;		fin.open (fileName, ios::in);
				if (!fin.good()) {	
					cout << "\n XMLparser::Unable to read the file: " << fileName;
					return	false;	
				}
												//assert (fin.good());

	char	ch, *word; 
			if (textLine == NULL) 	textLine 	= 	new char[1000];
			if (firstWord == NULL) 	firstWord 	= 	new char[1000];
	stack<int>	rElStack;
	
	int		 uc = 0;// MAXCHARS=1;
	//char	*unitChars = new char[MAXCHARS];
	int			cLineNum = 0;
	bool		elementExpected = false;
	long int		pBeginLine;			
	XMLelement		*rootElement = NULL;
	bool			elmAlert=false;
	vector<char*>	bufferedNames;
	//------------------------------------------------------------
		while (!fin.eof()) {
						
			pBeginLine = fin.tellg();

			fin.getline (textLine, 300);		assert (strlen(textLine) < 299);
			sscanf (textLine, "%s", firstWord);		//cout << "\n firstWord: " << firstWord;
			cLineNum ++;
			if (firstWord[0] == '%' || strlen(textLine) < 2) { continue; }	
		//	rootElement = NULL;
			//cout << "\n " << textLine;
			// TOKENIZE		< > </	/>	= 	
			int		lineLength = strlen (textLine);
			
			for (int k=0; k<lineLength; ++k) {
				
				if (textLine[k] == '<') {	
					
					if (k != lineLength-1 && textLine[k+1] == '/') {	
						rElStack.pop();
						elmAlert = false;
						
					} else {
							if (rElStack.empty()) {
								rootElement 	= new XMLelement;
								elmAlert		= true;
								elementList.push_back (rootElement);
								rootElement->filePointer = pBeginLine;
							}
							rElStack.push (1);
					}
					uc = 0;
					
				} else if (textLine[k] == '=') {
					if (uc > 0) {
						if (elmAlert) {
							bufferedNames.push_back (makeString(unitChars, uc));
						}		
					}
					uc = 0;
					
				} else if (textLine[k] == '/') {
					if (k != lineLength-1 && textLine[k+1] == '>') {	
						rElStack.pop();
						if (uc > 0 && elmAlert) {
							bufferedNames.push_back (makeString(unitChars, uc));
						}
						if (elmAlert)
							rootElement->assignAttributes (bufferedNames);
						elmAlert = false;
						uc = 0;
					} else {
						unitChars[uc++] = textLine[k];	
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
					}
				} else if (textLine[k] == '>') {	
					if (uc > 0 && elmAlert) {
							bufferedNames.push_back (makeString(unitChars, uc));	
					}
					if (elmAlert)
						rootElement->assignAttributes (bufferedNames);
					elmAlert = false;
					uc = 0;
				} else if (textLine[k] == ' ' || textLine[k] == '\t') {
					if (uc > 0 && elmAlert) {
						bufferedNames.push_back (makeString(unitChars, uc));	
					}
					uc = 0;
				} else {
					if (textLine[k] != '\"')
						unitChars[uc++] = textLine[k];
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
				
				}	
					

			}// For each char in the line: 	
			
		}//--------------------------------------------------------------
		return true;
			
	
		//cout << "\n\n ROOT Elements -------------------- ";
		for (int k=0; k<elementList.size(); ++k) {
			//			elementList[k]->print();
						elementList[k]->readFullElement (this);
		}
		
		for (int k=0; k<elementList.size(); ++k) {
						elementList[k]->freeUp();
		}
		
		for (int k=0; k<elementList.size(); ++k) {
						elementList[k]->print(1);
		}
		return true;
		getchar();
		
		for (int k=0; k<elementList.size(); ++k) {
						elementList[k]->readFullElement (this);
		}
		for (int k=0; k<elementList.size(); ++k) {
						elementList[k]->print(1);
		}
		
		return true;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
	
void
XMLelement::freeUp () {
	for (int i=0; i<childs.size(); ++i)
					delete childs[i];
	childs.clear();
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
		
	
	
	
int
XMLelement::assignAttributes (vector<char*> &  bufferedNames) {
						
	//cout << "\n\t\t Assigning Attributes ";  //[" << bufferedNames[0] << "] ++ ";
	//for (int i=0; i<bufferedNames.size(); ++i) {
	//	cout << " [" << bufferedNames[i] << "]" << flush;	if (i==0) cout << " ++ ";
	//} cout << flush;


	if (bufferedNames.size() == 0) {
		cout << "\n ???? ERROR: No bufferred Names given to assignAttributes()" << flush; return 0; 
	}
//	assert (this->name == NULL);
	
	if (this->name != NULL) {
		//cout << "\n assignAttributes ():: the element already has a name: " << this->name; getchar();
		for (int i=0; i<bufferedNames.size(); ++i) delete [] bufferedNames[i];
		bufferedNames.clear(); return 1;
	}
	
		this->name = bufferedNames[0];
																// getchar();
		if (((bufferedNames.size()-1) % 2) != 0) {
			cout << "\n ???? ERROR: assignAttributes(): Total number of Buffered Names should be Even " << flush;
				cout << "\n\t\t Assigning Attributes ";  //[" << bufferedNames[0] << "] ++ ";
				for (int i=0; i<bufferedNames.size(); ++i) {
					cout << " [" << bufferedNames[i] << "]" << flush;	if (i==0) cout << " ++ ";
				} cout << flush;
			return 0;		
		}

		
	for (int i=1; i<bufferedNames.size(); ) {
			this->attributes.push_back (new XMLattribute);
			this->attributes.back()->name 	= bufferedNames[i++];
			this->attributes.back()->value 	= bufferedNames[i++];
	}
	
	bufferedNames.clear();	
	return 1;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


	
void
XMLelement::setContent (char*  givenString) {
	
	if (content == NULL) {
		content = new char[strlen(givenString)+1];
	} else {
		delete [] content;
		content = new char[strlen(givenString)+1];
	}
	strcpy (content, givenString);
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
void
XMLelement::addContent (char*  givenString) {
	//	content = new char[1000];
	//	content[0] = '\0';
	char *temp;
	if (content == NULL) {
		content = new char[strlen(givenString)+1];
		content[0] = '\0';
	} else {
		temp = content;
		content = new char[strlen(temp)+strlen(givenString)+20];
		//cout << "\n Memcpy " << (strlen(temp)+1) << " to  " << strlen(temp)+strlen(givenString)+20;
		//content = new char[5000];
		//content[0] = '\0';
		memcpy (content, temp, (strlen(temp)+1)*sizeof(char));
		//cout << "\n After a memcpy[cont]: " << content;
		//cout << "\n After a memcpy[temp]: " << temp;
		delete [] temp;
	}
	strcat (content, givenString);
	//cout << "\n After adding the content:+" << content << flush; //getchar();
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
	
	
void
XMLelement::setContent (char*  unitChars, int uc) {
	
	if (content == NULL) {
		content = new char[uc+2];
	} else {
		delete [] content;
		content = new char[uc+2];
	}
	//cout << "\n Setting Content ";	// Remove the initial blank spaces.
	//unitChars[uc] = '\0';
	//cout <<" CONTENT [" <<  unitChars << "]" << uc; 
	
	int k=0;	bool firstTime = true;
	for (int i=0; i<uc; ++i) {
		if (firstTime && (unitChars[i] == ' ' || unitChars[i] == '\t' || unitChars[i] == '\n') 
											  || ((int)unitChars[i]) == 13) {	
			continue;
		} 
			firstTime = false;
			content[k++] = unitChars[i];		// cout << content[i];
	}
				// Remove the trailing blank spaces
	//content[k] = '\0';
	//cout <<" CONTENT [" <<  content << "]" << k; 
	k--;			 
	while (k >= 0) {
		if (content[k] == ' ' || content[k] == '\t' || content[k] == '\n' 
													|| ((int)content[k]) == 13)
			k--;
		else
			break;
	}
	
	content[k+1] = '\0';	return;
	cout <<" CONTENT [" <<  content << "]" << k+1;
	
	if (k < 4)
	for (int i=0; i<=k; ++i)
		if (content[i] == ' ') cout << "\n  BLANK";
		else if (content[i] == '\n') cout << "\n  LINE";
		else if (content[i] == '\t') cout << "\n  TAB";
		else						 cout << "\n Encoding: " << (int) content[i] << " ";
	getchar();
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
	
		
			
void		
XMLelement::readFullElement (XMLparser	*parser) {
	
	fstream	&	fin = parser->fin;
		assert (filePointer != -1);		fin.clear();
		fin.seekg (filePointer);
	//cout << "\n\n\n ++++++++++++++++++++++++++++++++++++++ Reading Full Element: " << name;
	char		ch, *word;
	char	*& 	textLine 	= 	parser->textLine;
	char	*& 	firstWord 	= 	parser->firstWord;
	char	*& 	unitChars 	= 	parser->unitChars;
	int		 & 	MAXCHARS 	= 	parser->MAXCHARS;
	
				if (textLine == NULL) 	textLine 	= 	new char[1000];
				if (firstWord == NULL) 	firstWord 	= 	new char[1000];
	
					
	int		 uc = 0;
	int		cLineNum = 0;
	bool			elementExpected = false;
	bool			elmAlert=false, contentAlert = false, firstTime = true, continuousBlanks = true;
	vector<char*>	bufferedNames;
	XMLelement		*ePopped=NULL; char *eThere = NULL;
	//------------------------------------------------------------

	stack<XMLelement*>	rElStack;
										rElStack.push(this);
	XMLelement			*myElement;					
	//-+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ 
		while (!fin.eof()) {
			fin.getline (textLine, 300);		assert (strlen(textLine) < 299);
			sscanf (textLine, "%s", firstWord);	
			if (firstWord[0] == '%' || strlen(textLine) < 2)  continue; 
					
			bool hasCharacters = false;	int ii=0;
			while (true) {
				if (textLine[ii] != '\t' && textLine[ii] != ' ') {hasCharacters = true; break;}
				ii++;
				if (textLine[ii] == '\0') break;
			}
			if (!hasCharacters) continue;
			 //cout << "\n -- textLine: " << textLine;
			 //cout << "\n\t --firstWord: " << firstWord;
	//		myElement = NULL;
			int		lineLength = strlen (textLine);
			//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
			for (int k=0; k<lineLength; ++k) {
				
				if (textLine[k] == '<') {	
					
					if (k != lineLength-1 && textLine[k+1] == '/') {	
						if (contentAlert && !rElStack.empty()) {
							rElStack.top()->setContent(unitChars, uc);
						} 
						contentAlert 	= false;
						ePopped = rElStack.top();	rElStack.pop();
						//if (ePopped->name != NULL)
						//cout << "\n POPPED out: " << ePopped->name << flush;
						elmAlert = false;
						k++;	// skipping the '/'	
					} else {
							if (rElStack.empty()) {
										break;
							} else {
								if (!firstTime) {
											if (contentAlert && !rElStack.empty()) {
												rElStack.top()->setContent(unitChars, uc);
											}	
									myElement 	= new XMLelement;
									rElStack.top()->childs.push_back(myElement);
									elmAlert		= true;
									contentAlert 	= false;
									rElStack.push (myElement);
								} else {
									myElement		= rElStack.top();
									elmAlert 		= true;
									contentAlert 	= false;
									firstTime 		= false;
								}
									
							}
					}
						uc = 0;
					
				} else if (textLine[k] == '=') {
					if (uc > 0) {
						if (elmAlert) {
							bufferedNames.push_back (parser->makeString(unitChars, uc));
						}		
					}
					uc = 0;
					
				} else if (textLine[k] == '/') {
					if (k != lineLength-1 && textLine[k+1] == '>') {	
						ePopped = rElStack.top(); rElStack.pop();
						//if (ePopped->name != NULL)
						//cout << "\n POPPED out: " << ePopped->name << flush;
						if (uc > 0 && elmAlert) {
							bufferedNames.push_back (parser->makeString(unitChars, uc));
						}
						if (elmAlert)
							myElement->assignAttributes (bufferedNames);
						elmAlert = false;
						uc = 0;
						k++;
					} else {
						unitChars[uc++] = textLine[k];	
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
					}

					
				} else if (textLine[k] == '>') {	
							
					if (uc > 0 && elmAlert) {
							bufferedNames.push_back (parser->makeString(unitChars, uc));	
					}
					if (elmAlert) 	myElement->assignAttributes (bufferedNames);
					else {
						if (ePopped != NULL) {
							if (uc > 0) {
								eThere = parser->makeString(unitChars, uc);
								//cout <<"\n COMPARING: ["<< ePopped->name << "]--[" << eThere << "]";
								if (strcmp(ePopped->name, eThere)) {
									cout <<"\n\n\t BAD-XML: ["<< ePopped->name << "]--["<<eThere<<"]";
									cout << " Error \n ------ Printing Stack"; 
									while (!rElStack.empty()) {
										rElStack.top()->print();
										rElStack.pop();
									}
									cout << " Error \n\n"; 
									exit(0);
								}
								//getchar();
							}
						}
					}
					if (elmAlert) 	contentAlert = true;
					else			contentAlert = false;
					elmAlert = false;
							
					uc = 0;
				} else if (((textLine[k] == ' ' || textLine[k] == '\t'))) {
					if (!contentAlert) {		
						if (uc > 0 && elmAlert) {
							bufferedNames.push_back (parser->makeString(unitChars, uc));	
						}
							uc = 0;
					} else {
						if (!continuousBlanks) {
							unitChars[uc++] = textLine[k];
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
							continuousBlanks = true;
						}
					}
				} else {
					if (textLine[k] != '\"')
						unitChars[uc++] = textLine[k];
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
				
				}	
				if (textLine[k] != ' ' && textLine[k] != '\t') {	
					continuousBlanks = false;
				}
					
			}// For each char in the line: 	
	
					//if (rElStack.top()->name != NULL)
					if (!elmAlert)
						unitChars[uc++] 	= '\n';
					continuousBlanks 	= false;
									
					if (rElStack.empty()) {
						//cout << "\n BREAKING ";
						break;	
					}
		}//--------------------------------------------------------------
			
		//cout << "\n *******************************************************************";
		//	this->print(1);
		//cout << "\n *******************************************************************" << flush;
		//getchar();
			if (!rElStack.empty()) {
				cout << "\n BAD XML Syntax ";
									while (!rElStack.empty()) {
										rElStack.top()->print();
										rElStack.pop();
									}
				cout << "\n-------------\n"; exit(0);
			}
	
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
			





		
void
XMLelement::tokenizeLineWise (char *contArray, vector<char*> & lineWords, 
																vector<int> & nWordsEachLine,
																bool 		alsoPrint) {

	for (int i=0; i<lineWords.size(); ++i) delete [] lineWords[i]; 	      lineWords.clear();		
																	 nWordsEachLine.clear();
	if (contArray == NULL || !strcmp(contArray, ""))	return;						
	
	int		length = strlen (contArray);	
								if (alsoPrint)
								cout << "\n CONTENT++[[" << contArray << " len:" << length;
	char	*buf = new char[1000], *word = new char[1000], *sw;
	int		i = 0;
	for (int k=0; k<length+1; ++k) {
		buf[i++] = contArray[k];
		if (contArray[k] == '\n' || contArray[k] == '\0') {
			if (alsoPrint)
			cout << "\n\t\t GOT LINE:[" << buf;
			int w=0, nWords=0;
			for (int j=0; j<i; ++j) {
				word[w++] = buf[j];
				if (buf[j] == '\t' || buf[j] == ' ' || j == i-1) {
					if (w > 1) {
						if (j != i-1) w--;
						word[w] = '\0';
						sw = cloneString(word);
						lineWords.push_back (sw);
						nWords ++;
					}
					w = 0;
				}
			}
			i = 0;
			if (nWords > 0)
			nWordsEachLine.push_back (nWords);
											if (contArray[k] == '\0') break;
		}
	}
	if (alsoPrint)  {
		cout << "\n Printing the line-Words: ";
		for (int n=0,start=0; n<nWordsEachLine.size(); ++n) {
				cout << "\n\t [";
			for (int k=start; k<start+nWordsEachLine[n]; ++k) {
					if (k != start) cout << "--";
					cout << lineWords[k];
			}
			cout <<"]";
			start += nWordsEachLine[n];
		}
	}
	delete [] buf;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
	

	
void
XMLparser::tokenizeLineWise (char *contArray, vector<vector<char*> > & lines) {
	
	// lines.clear();		
							//	if (contArray[0] == '\n') return;
	lines.clear();		





		if (contArray == NULL || !strcmp(contArray, ""))	return;						
	int		length = strlen (contArray);	
							//	cout << "\n CONTENT++[[" << contArray << " " << length;
	
	vector<char*>		myLine;
	lines.push_back (myLine);
	
	char	*buf = new char[1000], *word = new char[1000], *sw;
	int		i = 0;
	for (int k=0; k<length+1; ++k) {
		buf[i++] = contArray[k];
		
		if (contArray[k] == '\n' || contArray[k] == '\0') {
			//cout << "\n\t\t GOT LINE:[" << buf;
			int w=0;
			for (int j=0; j<i; ++j) {
				word[w++] = buf[j];
				if (buf[j] == '\t' || buf[j] == ' ' || j == i-1) {
					if (w > 1) {
						word[w] = '\0';
						sw = cloneString(word);
						lines.back().push_back (sw);
					}
					w = 0;
				}
			}
			i = 0;
											if (contArray[k] == '\0') break;
			vector<char*>		myLine;
			lines.push_back (myLine);
		}
	}
	cout << "\n Printing the lines: ";
	for (int k=0; k<lines.size(); ++k) {
		cout << "\n ++++++";
		for (int i=0; i<lines[k].size(); ++i) {
			cout << " + " << lines[k][i];
		}
	}
	delete [] buf;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
		
void
XMLparser::tokenizeLineWise (char *contArray, vector<char*> & lineWords, 
																vector<int> & nWordsEachLine,
																bool 		alsoPrint) {
	for (int i=0; i<lineWords.size(); ++i) delete [] lineWords[i]; 	      lineWords.clear();		
																	 nWordsEachLine.clear();

	if (contArray == NULL || !strcmp(contArray, ""))	return;						
	
	int		length = strlen (contArray);	
								if (alsoPrint)
								cout << "\n CONTENT++[[" << contArray << " len:" << length;
	char	*buf = new char[1000], *word = new char[1000], *sw;
	int		i = 0;
	for (int k=0; k<length+1; ++k) {
		buf[i++] = contArray[k];
		if (contArray[k] == '\n' || contArray[k] == '\0') {
			if (alsoPrint)
			cout << "\n\t\t GOT LINE:[" << buf;
			int w=0, nWords=0;
			for (int j=0; j<i; ++j) {
				word[w++] = buf[j];
				if (buf[j] == '\t' || buf[j] == ' ' || j == i-1) {
					if (w > 1) {
						if (j != i-1) w--;
						word[w] = '\0';
						sw = cloneString(word);
						lineWords.push_back (sw);
						nWords ++;
					}
					w = 0;
				}
			}
			i = 0;
			if (nWords > 0)
			nWordsEachLine.push_back (nWords);
											if (contArray[k] == '\0') break;
		}
	}
	if (alsoPrint)  {
		cout << "\n Printing the line-Words: ";
		for (int n=0,start=0; n<nWordsEachLine.size(); ++n) {
				cout << "\n\t [";
			for (int k=start; k<start+nWordsEachLine[n]; ++k) {
					if (k != start) cout << "--";
					cout << lineWords[k];
			}
			cout <<"]";
			start += nWordsEachLine[n];
		}
	}
	delete [] buf;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
	
	

char *
XMLparser::cloneString (char *n) {
	char	*word = new char[strlen(n)+1];
	strcpy (word, n);
	return word;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


	

char *
XMLelement::cloneString (char *n) {
	char	*word = new char[strlen(n)+1];
	strcpy (word, n);
	return word;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


void
XMLparser::makeListOfMatchingElements (	char 					*requestedElementName, 
										char					*nameOfElementToAvoid,
										XMLelement 				*gElem, 
										vector<XMLelement*> &  	filteredList) {
					
																	queue<XMLelement*>		myQueue;
																	XMLelement				*myE, *childE;	
										myQueue.push (gElem);  								
		while (!myQueue.empty()) {
			myE = myQueue.front();	myQueue.pop();
			if (!strcmp (myE->name, requestedElementName)) {
				filteredList.push_back (myE); 
			} else if (nameOfElementToAvoid != NULL && !strcmp (myE->name, nameOfElementToAvoid)) {
								continue;  
			} else {
																					int	count = 0;
					do {
						childE = myE->getChild (count++);
															if (childE != NULL)  {
																	myQueue.push (childE);				
															}
					} while (childE != NULL);  	
			}
		}	
			
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_

bool
XMLparser::matchesElementNameOnly (char *eName, char *eNameWithoutNamespace) {
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



bool
XMLparser::searchElement (char *requiredElementName, 	XMLelement				*gElem,
														vector<char*> 			& requiredAttrVals, 
													 	vector<XMLelement*>		& matchingElementsV,
														bool 		 			toCheckRecursive) {
																									
																				matchingElementsV.clear(); 
	
		//cout << "\n -------- Inside SearchElement(): {" << requiredElementName << "} in [" << gElem->name << "]";	
	//	cout << "\n SearchElement() --------------"; 
	//	cout << "\n                    Looking for: "; cout << " [" << requiredElementName << "] "; 
		for (int i=0; i<requiredAttrVals.size()/2; ++i) 
									cout << "  " << requiredAttrVals[2*i] << "=" << requiredAttrVals[2*i+1];
	//	cout << "\n Searching started with element: "; gElem->printAttributes(); 

											
																	queue<XMLelement*>		myQueue;
																	XMLelement				*myE, *childE;	
										myQueue.push (gElem);  								
		while (!myQueue.empty()) {
			myE = myQueue.front();	myQueue.pop();
			//if (!strcmp (myE->name, requiredElementName)) 
			if (matchesElementNameOnly (myE->name, requiredElementName)) {
								// cout << "\n Trying to match with element: "; myE->print();
																			bool matched = true;
				for (int i=0; i<requiredAttrVals.size()/2; ++i) {
						if ( ! myE->hasAttributeValue(requiredAttrVals[2*i], requiredAttrVals[2*i+1])) {
								// cout << "\n\t\t\t\t\t Matched to element "; myE->print();
								matched = false; break;
						}
				}				
						if (matched) {
							matchingElementsV.push_back (myE); 
						}
							
			} else if (!toCheckRecursive) {
								continue;  
			} else {
																					int	count = 0;
					do {
						childE = myE->getChild (count++);
															if (childE != NULL)  {
																	myQueue.push (childE);				
															}
					} while (childE != NULL);  	
			}
		}	
			
	for (int i=0; i<matchingElementsV.size(); ++i) {
	//	cout << "\n         __Matched with element: "; matchingElementsV[i]->printAttributes(); 
	}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


bool
XMLparser::searchKeyword (char *keyword,	XMLelement				*gElem,
											vector<int> 			& matchesWithWhat, 
											vector<XMLelement*>		& matchingElementsV,
											bool 					toCheckRecursive) {
	matchingElementsV.clear(); 	
	matchesWithWhat.clear(); 
		
		cout << "\n ------------------------------------------------- Inside SearchKeyword (): ";	
		cout << "\n [" << keyword << "] "; 
		cout << "\n Keyword-Search started with element: "; gElem->print(); 
		
																	queue<XMLelement*>		myQueue;
																	XMLelement				*myE, *childE;	
										myQueue.push (gElem);  								
		while (!myQueue.empty()) {
			myE = myQueue.front();	myQueue.pop();
			if (!strcmp (myE->name, keyword)) {
								matchesWithWhat.push_back (0); 
								matchingElementsV.push_back (myE); 
			} else {
						for (int k=0; k<myE->attributes.size(); ++k) {
							if (!strcmp (myE->attributes[k]->name, keyword)) {
								matchesWithWhat.push_back (1);
								matchingElementsV.push_back (myE); 
							} else if (!strcmp (myE->attributes[k]->value, keyword)) {
								matchesWithWhat.push_back (2); 
								matchingElementsV.push_back (myE); 
							}	
						}
			}

			if (!toCheckRecursive) {
								continue;  
			} else {
																					int	count = 0;
					do {
						childE = myE->getChild (count++);
															if (childE != NULL)  {
																	myQueue.push (childE);				
															}
					} while (childE != NULL);  	
			}
		}	
			
	for (int i=0; i<matchingElementsV.size(); ++i) {
		cout << "\n __Matched Keyword with element ";
		if (matchesWithWhat[i]==0) 	cout << " with-Element-Name ";   
		if (matchesWithWhat[i]==1)	cout << " with-Attr  ";
		if (matchesWithWhat[i]==2)	cout << " with-Attr-value "; 
		matchingElementsV[i]->print(); 
	}

		
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_




bool 
XMLparser::matchesToken (char *dataBuf, char *gToken) {
		// It should be ensured before using this function that dataBuf should have at least the length of token. 
												int tlen = strlen(gToken); 
												if (strlen(dataBuf) < tlen) return false; 
						//	cout << "\n Matching: [" << dataBuf << "]  [" << gToken << "]";					
	for (int i=0,n=0; i<tlen; ++i,++n)		
		if (dataBuf[i] != gToken[n])
			return false;
	return true;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_


//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
void
XMLparser::ifNecessaryReallocate (char *& gChars, int uc, int & MAXCHARS) {
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] gChars;
											gChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



int
XMLparser::calculateLineNumber (fstream &fin, int requestedBytes, int bufferReadUpto) {
		
		long int pCurrentPos = fin.tellp();
	   			pCurrentPos = pCurrentPos - (long int)requestedBytes + (long int) bufferReadUpto; 
				//cout << "\n Requested Bytes: " << requestedBytes;
				//cout << "\n bufferReadUpto : " << bufferReadUpto;
				//cout << "\n pCurrentPos    : " << pCurrentPos;
		long int 		bytesToRead = pCurrentPos;
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
						if (nowAt+i >= pCurrentPos) { reachedRequiredLine = true; break; }
					}
	
							//	dataBuf[requestedBytes] = '\0';
							//	cout <<"\n--------------------- READ DATABUF: " << "[" << dataBuf <<"]";
		}
		//cout << "\n Determined lineCount: " << lineCount;
		return lineCount;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



void
XMLparser::flagError (stack<XMLelement*> & rElStack, char *dataBuf, 
							int requestedBytes, int bufferReadUpto, char *gToken, int msgCode) { 
																								int	 lineCount=-1;
	if (msgCode > 0 || 1==1) {
		lineCount = calculateLineNumber (fin, requestedBytes, bufferReadUpto);
		char *onlyFileName = NULL;
		if (this->fileName != NULL) {
			onlyFileName = new char[strlen(this->fileName)+1];
			strcpy (onlyFileName, this->fileName);
				int	 bg;
			for (bg=strlen(onlyFileName); bg>=0; --bg) {
				if (onlyFileName[bg] == '/') {
					break;
				}
			}
			for (int k=bg+1; k<=strlen(onlyFileName); ++k) 
				onlyFileName[k-bg-1] = onlyFileName[k];
		}

		cout << "\n\n [";
		if (onlyFileName != NULL) cout << onlyFileName;
	    cout << " Line:"<<lineCount
			 << "] --STOPPED--STOPPED--STOPPED--STOPPED--STOPPED--STOPPED--STOPPED--STOPPED--STOPPED--STOPPED--";
		cout << "\n Status of dataBuf: [";
	    for (int i=0; i<requestedBytes; ++i) {
			cout << dataBuf[i]; 
		}	
		cout << "]";
		cout << "\n [";
		if (onlyFileName != NULL) cout << onlyFileName;
		cout << " Line:" << lineCount << "] ------------------- Error when parsing token: {" << gToken << "}";
		cout << "\n [";
		if (onlyFileName != NULL) cout << onlyFileName;
		cout << " Line:" << lineCount << "] ------------------- BAD XML Syntax ";
	} else {
		cout << "\n Status of dataBuf: [";
	    for (int i=0; i<requestedBytes; ++i) {
			cout << dataBuf[i]; 
		}	
		cout << "]";
	}//----------------------------------------  <><><><><><><><><><><><><><><><><><><><>
	 	if (msgCode == 1) {
			cout << "\n\t [Line: " << lineCount << "]";
			cout << "  >>The token (" << gToken << ") was encountered in an illegal state. (state_rE = true) "; 
		}
		if (msgCode == 2) {
			cout << "\n\t [Line: " << lineCount << "]";
			cout << " >>>At token (" << gToken << ") BAD XML encountered. Tags were mismatched.  "; 
		}
				cout << "\n------------------- Status of element-stack -----------------------------------------";
				vector<XMLelement*>  rElVector; 
									while (!rElStack.empty()) {
												rElStack.top()->print();
												rElVector.push_back (rElStack.top());
											rElStack.pop();
									}
				for (int i=rElVector.size()-1; i>=0; --i) {
					rElStack.push (rElVector[i]);
				}					
				cout << "\n-------------\n" << flush; //exit(0);
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_




//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
bool
XMLparser::readXMLdocument (char *fileName) {
														char *onlyFileExtension = new char[strlen(fileName)+1];
														strcpy (onlyFileExtension, fileName);
															int	 bg;
															for (bg=strlen(onlyFileExtension); bg>=0; --bg) {
																	if (onlyFileExtension[bg] == '.') {
																				break;
																	}
															}
														for (int k=bg+1; k<=strlen(onlyFileExtension); ++k) 
															onlyFileExtension[k-bg-1] = onlyFileExtension[k];
																	
														for (int i=0,len=strlen(onlyFileExtension); i<len; ++i) {
																int ich = (int) onlyFileExtension[i];
																if (ich >= 65 && ich <= 90) {
																	onlyFileExtension[i] = (unsigned char)(ich + 32); 
																}
														}
														if (strcmp (onlyFileExtension, "xml") && 
															strcmp (onlyFileExtension, "xsd")) {
															cout << "\n\n --------------------------- Given Document: " 
																											<< fileName;
															cout << "\n Provide Extension of Input Document as (.xml) or (.xsd) ";
															cout << "\n\n"; exit (0);
														}
	

	XMLparser	*parser = this;		 this->reset();
										//fstream 	fin;
																			bool error = false;
	if (this->fileName != NULL) delete [] this->fileName;
	this->fileName = new char[strlen(fileName)+1];
	strcpy (this->fileName, fileName);		
	
										fin.open (fileName,ios::in|ios::binary);
				if (!fin.good()) {	
					cout << "\n ,,,,,,,,,,,XMLparser::Unable to read the file: " << fileName;
					fin.clear(); fin.close();	// assert (fin.good());
					return	false;	
				}
	//----------------------------------------	
		fin.seekg (0, ios::end);
		long int 		totalFileSize = fin.tellg();
		long int		bytesLeft;		
		fin.seekg (0, ios::beg);
	//----------------------------------------	
		char *token0 	= new char[2]; strcpy (token0, "<"); 
		char *token1 	= new char[3]; strcpy (token1, "</"); 
		char *token2 	= new char[2]; strcpy (token2, ">"); 
		char *token3 	= new char[3]; strcpy (token3, "/>"); 
		char *token4 	= new char[2]; strcpy (token4, "="); 
		char *token51 	= new char[2]; strcpy (token51, " "); 
		char *token52 	= new char[2]; strcpy (token52, "\t"); 
		char *token53 	= new char[2]; strcpy (token53, "\n"); 
		char *token6 	= new char[3]; strcpy (token6, "%"); 
		char *token7 	= new char[3]; strcpy (token7, "<?"); 
		char *token8 	= new char[3]; strcpy (token8, "/"); 
		char *token9 	= new char[3]; strcpy (token9, "\""); 
		char *token10 	= new char[3]; strcpy (token10, "\\"); 
		if (1==2) {
			cout << "\n Printing the tokens: ";
			cout << "\n [" << token0 << "]";
			cout << "\n [" << token1 << "]";
			cout << "\n [" << token2 << "]";
			cout << "\n [" << token3 << "]";
			cout << "\n [" << token4 << "]";
			cout << "\n [" << token51 << "]";
			cout << "\n [" << token52 << "]";
			cout << "\n [" << token53 << "]";
			cout << "\n [" << token6 << "]";
			cout << "\n [" << token7 << "]";
			cout << "\n [" << token8 << "]";
			cout << "\n [" << token9 << "]";
			cout << "\n [" << token10 << "]";
		}
	//----------------------------------------	
				bool	state_rA = false;	// reading Attribute
				bool	state_rE = false;	// reading Element
				bool	state_rC = false;	// reading Content
				bool	state_rB = false;	// reading binary data. 
				bool	state_LC = false;	// parsing off line comment. 
				bool	state_CC = false;	// parsing off continued comment. 
													// Continued blanks CB  
	//----------------------------------------	
	
	cout << "\n            Reading XML Document: [" << fileName << "]";
	char		ch, *word;
	char	*& 	dataBuf 	= 	parser->textLine;
	char	*& 	firstWord 	= 	parser->firstWord;
	char	*& 	unitChars 	= 	parser->unitChars;
	int		 & 	MAXCHARS 	= 	parser->MAXCHARS;
	
				if (firstWord == NULL) 	firstWord 	= 	new char[1000];
	

	int		uc = 0, _bufSize = 29, requestedBytes;			
	int		cLineNum = 0;
	bool			elementExpected = false, continuedComment; 
	bool			firstTime = true, continuousBlanks = true;
	vector<char*>	bufferedNames;
	XMLelement		*ePopped=NULL; char *eThere = NULL;
				if (dataBuf == NULL) 	dataBuf 	= 	new char[_bufSize];
	//------------------------------------------------------------
									
	stack<XMLelement*>	rElStack;
	XMLelement			*myElement = new XMLelement;	
										 rElStack.push (myElement);
										 elementList.push_back (myElement);
	//-+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+
					continuedComment = false;	//state_CC = false;
	//-----------------------------------------------------------
	while (!fin.eof()) {
						
			pCurrentPos = fin.tellg();
									
					requestedBytes = ((bytesLeft=totalFileSize-pCurrentPos) > _bufSize) ? 
																		_bufSize : bytesLeft;
					
					//cout << "\n\n\n Requested Bytes: " << requestedBytes << flush;
					if (requestedBytes == 0) break;
							
					fin.read ((char*)dataBuf, requestedBytes);
									//		dataBuf[requestedBytes] = '\0';
									//		cout <<"\n---------------- READ DATABUF: " << "[" << dataBuf <<"]"<<flush;
					int		 k=0;
				//------------------------------	
				// CHECK if we are in state_LC or state_CC. 
				if (matchesToken (&dataBuf[k], token6) || state_LC || matchesToken(&dataBuf[k],token7)) {
						 //cout << " Continued Comment ";			// token6 = "%" token7="<?"
				 									state_LC = true;
							//k++;	
						for (; k<requestedBytes; ++k)  {
							if (dataBuf[k] == '\n') {
								state_LC = false;
								break;
							}
								//	if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 3, 
								//									totalFileSize)) {
								//		cout << "\n\n\t ERROR: Incomplete XML document";
								//	}
						}	
				}	
					
				if (state_CC) {
					checkXMLcomment (dataBuf, k, requestedBytes, state_CC, _bufSize, 
									 totalFileSize);		
					// This call will either parse-off the comment or will exhaust requestedBytes.
					// Hence will not execute the subsequent for loop.  
				}
				
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
		//		When this for loop is entered, we are not in state_CC or state_LC. 
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
		for (; k<requestedBytes; ++k) {
												if (1==2) {
														cout << "\n " << uc << "   ";
														if (dataBuf[k] != '\n')
														cout <<"{" << (char)dataBuf[k] << "}" << flush;
														else
														cout <<"{\\n}" << flush;
														cout << "  " << bufferedNames.size();
												}
											
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token '<' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				//
				// A '<' could be 1. the start of an xml comment: So parse it off.  
				// 										
				//                2. the start of an element: Instantiate a new xml element and push it into
				//                							  the stack. 
				//                							  The state changes to state_rE = true.  
				//       									  All other states can be made false. 	
				if (matchesToken(&dataBuf[k], token0)) {	// token0= '<'
							if (checkXMLcomment (dataBuf, k, requestedBytes, state_CC, _bufSize, 
												 totalFileSize))
							continue;	// Though we write continue, actually it has either parsed off the comment, or
										// has exhausted requestedBytes and will take control out of this loop. 
					if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 1, 
																		totalFileSize)) break;	
					assert (dataBuf[k] == '<');
					//cout << "\n Here --------------- "; 
					if (state_rA) {
							unitChars[uc++] = dataBuf[k];	
										ifNecessaryReallocate (unitChars, uc, MAXCHARS);
					} else
					if (! matchesToken (&dataBuf[k],  token1)) {	 // token1 = '</'
								if (!firstTime) {
											if (state_rC && !rElStack.empty()) {
												rElStack.top()->setContent(unitChars, uc);
											}	
									myElement 	= new XMLelement;
									myElement->filePointer = pCurrentPos + k; 
									if (!rElStack.empty()) {
										 rElStack.top()->childs.push_back (myElement);
										 myElement->parent = rElStack.top(); 
									} else {
										elementList.push_back (myElement);
									}
														
									rElStack.push (myElement);
								} else {
									//cout << "\n First time execution ";
									myElement		= rElStack.top();
									myElement->filePointer = pCurrentPos + k; 
									firstTime 		= false;
								}
									state_rE 	= true;
									state_rC 	= false;
								 			 uc = 0;
															//flagError (rElStack, dataBuf, requestedBytes, k,
															//			   	token0, 0);
									/*
									myElement->print(); 
									cout << "\n------------------- Printing element-stack content ";
										vector<XMLelement*>  rElVector; 
										assert (!rElStack.empty()); 
										while (!rElStack.empty()) {
													rElStack.top()->print();
													rElVector.push_back (rElStack.top());
												rElStack.pop();
										}
												for (int i=rElVector.size()-1; i>=0; --i) {
													rElStack.push (rElVector[i]);
												}					
									*/ 			
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token '</' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				// A '</' marks the closing tag. 
				// 				Pop out the element from the element tag. 
					} else {
																	if (state_rE == true) {
																		flagError (rElStack, dataBuf, requestedBytes,
																			   	k, token1, 1);
																		assert (error);
																	}
						if (state_rC && !rElStack.empty()) {
							rElStack.top()->setContent (unitChars, uc);
						}	
						ePopped = rElStack.top();	rElStack.pop();
										//if (ePopped->name != NULL)
										//cout << "   POPPED out: " << ePopped->name << flush;
						state_rC = false;
						assert (state_rE == false);
						assert (state_rA == false);
						k++;	// skipping the '/'	
						uc = 0;
					}
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token '=' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				} else if (matchesToken (&dataBuf[k], token4)) {	// '=' 
					if (uc > 0) {
						if (state_rE && !state_rA) {
							bufferedNames.push_back (parser->makeString(unitChars, uc));
							//state_rA = true;
							//cout << "\n Added: " << bufferedNames.back() <<"              ";
							uc = 0;
						}
					}
						if (state_rE && state_rA || state_rC) {  // '=' sign appeared within quotes 
																 //  or it appeared in content. 
							unitChars[uc++] = dataBuf[k];	
										ifNecessaryReallocate (unitChars, uc, MAXCHARS);
									
						}	
					
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token '/' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				// For a lonely '/' do nothing. 
				// 		This is considered as part of data and stored. 
				} else if (matchesToken (&dataBuf[k],token8) ) { //	'/'
								
					if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 1, totalFileSize)) 
																						break;
					assert (dataBuf[k] == '/');

					if (state_rA || state_rC) {
							unitChars[uc++] = dataBuf[k];
										ifNecessaryReallocate (unitChars, uc, MAXCHARS);
					} else
					if (! matchesToken (&dataBuf[k], token3)) { //  NOT '/>'
						unitChars[uc++] = dataBuf[k];	
										ifNecessaryReallocate (unitChars, uc, MAXCHARS);
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token '/>' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				//
				// A '/>' closes an element tag. 
					} else {
						ePopped = rElStack.top(); rElStack.pop();
																		assert (state_rE);
																		assert (!state_rC);
																		assert (!state_rA);
							if (uc > 0) 												
							bufferedNames.push_back (parser->makeString (unitChars, uc));
						if (state_rE) {
							if (!myElement->assignAttributes (bufferedNames)) {
															flagError (rElStack, dataBuf, requestedBytes, k,
																		   	token0, 0);
															assert (error); 
							}
						}
												// if (ePopped->name != NULL)
												// cout << "\n POPPED out: " << ePopped->name << flush;
						state_rE = false;
						uc = 0;
						k++;
					} 
							
					
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token '>' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				//
				// A '>' marks the 1. end of element-open tag: Store all the attributes. 
				//
				// 		 		or 2. end of element-close tag:  
				// 		 							Just pop off the element stack and verify that the two
				// 		 							elements are same. 
				} else if (matchesToken (&dataBuf[k], token2)) {	// '>'
									
					//cout << "\n -------------- WHY am I here again ??   " << uc << " ";			
					if (state_rA || state_rC) {  // This is rare: i.e. A '>' sign coming within 
												 // the quotes of attribute value. 
							unitChars[uc++] = dataBuf[k];
										ifNecessaryReallocate (unitChars, uc, MAXCHARS);
					} else {						
						if (state_rE) { // This is case 1.
								if (uc > 0)
								bufferedNames.push_back (parser->makeString(unitChars, uc));	
								if (!myElement->assignAttributes (bufferedNames)) {
															flagError (rElStack, dataBuf, requestedBytes, k,
																		   	token0, 0);
															assert (error); 
								}
								uc = 0;
						} else {	// This is case 2. Do error checking.  
							if (ePopped != NULL) {
								if (uc > 0) 
									eThere = parser->makeString(unitChars, uc);
								else {
									assert (bufferedNames.size() == 1);
									eThere = bufferedNames[0]; 
								}
									//cout <<"\n COMPARING: ["<< ePopped->name << "]--[" << eThere << "]";
									if (strcmp(ePopped->name, eThere)) {
													flagError (rElStack, dataBuf, requestedBytes, k,
																	   	token2, 2);
											cout <<"\n\t MIS-matched tags: ["<< ePopped->name << "]--["<<eThere<<"]";
											cout << " ..............ERROR \n\n"; 
											exit(0);
									}
									//getchar();
								
							}
							uc = 0;
						}
							if (state_rE) 	state_rC = true;
											state_rE = false;
					}

					
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token ' ' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				} else if (((dataBuf[k] == ' ' || dataBuf[k] == '\t'))) {
					//cout << "\n " << dataBuf << "  >>>>>>>>>>> " << k;
					//cout << "{b}"; 
					//												if (state_rC) cout << " state_rC"; 
					//												if (state_rA) cout << " state_rA";
					if (!state_rC && !state_rA) {		
						if (uc > 0) {		// Earlier it was (&& state_rE). Removed on 26-Mar'07
							bufferedNames.push_back (parser->makeString(unitChars, uc));
							//cout << "\n 1.Added: " << bufferedNames.back() <<"              ";
							//myElement->setName (parser->makeString(unitChars, uc));
							//cout << "\n READING ELE: " << myElement->name <<"  "<< flush;
						}
							uc = 0;
					} else {
						if (1==1 || !continuousBlanks) {		// 11-Mar'07 Just to preserve continuous blanks. 
							//cout << "--------b--------";
							//if (uc > 0)
							unitChars[uc++] = dataBuf[k];
										ifNecessaryReallocate (unitChars, uc, MAXCHARS);
						}
					}
							continuousBlanks = true;
					
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token '\n' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				} else if (dataBuf[k] == '\n') {
									//				if (state_rA) cout << " state_rA";
						if (!state_rC && !state_rA) {		
								if (uc > 0 && state_rE) 
								bufferedNames.push_back (parser->makeString(unitChars, uc));
								//cout << "\n 1.Added: " << bufferedNames.back() <<"              ";
								//myElement->setName (parser->makeString(unitChars, uc));
								//cout << "\n READING ELE: " << myElement->name <<"  "<< flush;
								uc = 0;
						}

													if (!state_rE) {
														if (uc > 0)
																unitChars[uc++] 	= '\n';
													}
													continuousBlanks 	= false;
													
													
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token '%' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				} else if (matchesToken (&dataBuf[k], token6)) {	// '%'
						if (state_rA) {
								unitChars[uc++] = dataBuf[k];	// cout << "*";
						} else {
						//if (dataBuf[k] == '%')  {
							//dataBuf[requestedBytes+1] = '\0';
							//cout << "\n COMMENT: Skipping line: " << dataBuf;
							for (; k<requestedBytes; ++k)  {
								if (dataBuf[k] == '\n') {
									break;
								}
							}	
								if (k==requestedBytes)	state_LC = true;
				
						//} else 
						//	k--;
						}
									
					
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token NOT ' \" ' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
				//} else if (!matchesToken (&dataBuf[k], token9)) { // != '\"') 
				//		unitChars[uc++] = dataBuf[k];	// cout << "*";
				//		
				//						ifNecessaryReallocate (unitChars, uc, MAXCHARS);
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token ' \" ' -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				} else if (matchesToken (&dataBuf[k], token9) ) { // == '\"') 
						if (state_rE) {
								if (state_rA)
									state_rA = false;
								else {
									state_rA = true; 
								}
						} else {
								unitChars[uc++] = dataBuf[k];	// cout << "*";
											ifNecessaryReallocate (unitChars, uc, MAXCHARS);
						}
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-Token ESCAPE ' \ ' ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				} else if (matchesToken (&dataBuf[k], token10) ) {
															//flagError (rElStack, dataBuf, requestedBytes, k,
															//			   	token0, 0);
						  //cout << "\n Encountered an escape character "; getchar();
									if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 2, 
																	totalFileSize)) {
										cout << "\n\n\t ERROR: Incomplete XML document";
									}
							
									unitChars[uc++] = dataBuf[k];	
												ifNecessaryReallocate (unitChars, uc, MAXCHARS);
									unitChars[uc++] = dataBuf[k+1];	
							k += 1; 
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~----------------
				//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- All other characters will be read ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				} else {
								unitChars[uc++] = dataBuf[k];	 //cout << "*";
											ifNecessaryReallocate (unitChars, uc, MAXCHARS);
				}
						

				//------------------------------------------------------------ 
				if (dataBuf[k] != ' ' && dataBuf[k] != '\t') {	
					continuousBlanks = false;
				}	
					
		}// For each char in the line: !_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
								
				//	continuousBlanks = false;
	}//--------------------------------------------------------------
			
		//cout << "\n *******************************************************************";
		//	this->print();
		//cout << "\n *******************************************************************" << flush;
		//getchar();
			if (!rElStack.empty()) {
				cout << "\n\n------------------- BAD XML Syntax ";
									while (!rElStack.empty()) {
											rElStack.top()->print();
											rElStack.pop();
									}
				cout << "\n-------------\n"; exit(0);
			}
			 fin.close(); 	fin.clear();
														delete [] token0; 
														delete [] token1; 
														delete [] token2; 
														delete [] token3; 
														delete [] token4; 
														delete [] token51; 
														delete [] token52; 
														delete [] token53; 
														delete [] token6; 
														delete [] token7; 
														delete [] token8; 
														delete [] token9; 
														delete [] token10; 
			return true;

}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_



//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
bool
XMLparser::readXMLdocument_old (char *fileName) {
	
	XMLparser	*parser = this;		 this->reset();
										//fstream 	fin;
	
	if (this->fileName != NULL) delete [] this->fileName;
	this->fileName = new char[strlen(fileName)+1];
	strcpy (this->fileName, fileName);		
	
										fin.open (fileName,ios::in|ios::binary);
				if (!fin.good()) {	
					cout << "\n ,,,,,,,,,,,XMLparser::Unable to read the file: " << fileName;
					fin.clear(); fin.close();	// assert (fin.good());
					return	false;	
				}
	//----------------------------------------	
		fin.seekg (0, ios::end);
		long int 		totalFileSize = fin.tellg();
		long int		bytesLeft;		
		fin.seekg (0, ios::beg);
	//----------------------------------------	
	
	cout << "\n            Reading XML Document: [" << fileName << "]";
	char		ch, *word;
	char	*& 	dataBuf 	= 	parser->textLine;
	char	*& 	firstWord 	= 	parser->firstWord;
	char	*& 	unitChars 	= 	parser->unitChars;
	int		 & 	MAXCHARS 	= 	parser->MAXCHARS;
	
				if (firstWord == NULL) 	firstWord 	= 	new char[1000];
	
	vector<char>		previousStates;				

	int		uc = 0, _bufSize = 29, requestedBytes;			
	int		cLineNum = 0;
	bool			elementExpected = false, continuedComment, xmlComment;
	bool			elmAlert=false, contentAlert = false, firstTime = true, continuousBlanks = true, 
																			attValueAlert = false;
	vector<char*>	bufferedNames;
	XMLelement		*ePopped=NULL; char *eThere = NULL;
				if (dataBuf == NULL) 	dataBuf 	= 	new char[_bufSize];
	//------------------------------------------------------------
									
	stack<XMLelement*>	rElStack;
	XMLelement			*myElement = new XMLelement;	
										 rElStack.push (myElement);
										 elementList.push_back (myElement);
	//-+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+
					continuedComment = false;	xmlComment = false;
	//-----------------------------------------------------------
	while (!fin.eof()) {
						
			pCurrentPos = fin.tellg();
									
					requestedBytes = ((bytesLeft=totalFileSize-pCurrentPos) > _bufSize) ? 
																		_bufSize : bytesLeft;
					
					//cout << "\n\n\n Requested Bytes: " << requestedBytes << flush;
					if (requestedBytes == 0) break;
							
					fin.read ((char*)dataBuf, requestedBytes);
										//	dataBuf[requestedBytes] = '\0';
										//	cout <<"\n--------------------- READ DATABUF: " << "[" << dataBuf <<"]";
					int		 k=0;
					//------------------------------
				if (dataBuf[k]== '%' || continuedComment || (dataBuf[k]=='<' && dataBuf[k+1]=='?')) {
					// cout << " Continued Comment ";
						//k++;	
						for (; k<requestedBytes; ++k)  {
							if (dataBuf[k] == '\n') {
								continuedComment = false;
								break;
							}
									if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 3, 
																	totalFileSize)) {
										cout << "\n\n\t ERROR: Incomplete XML document";
									}
						}	
				}	
					
				if (xmlComment) {
					checkXMLcomment (dataBuf, k, requestedBytes, xmlComment, _bufSize, 
									 totalFileSize);
				}
				
			//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
				
		for (; k<requestedBytes; ++k) {
			
				//if (dataBuf[k] != '\n')
				//cout <<"{" << (char)dataBuf[k] << "}" << flush;
				//else
				//cout <<"{\\n}" << flush;
				
				if (dataBuf[k] == '<') {	
							if (checkXMLcomment (dataBuf, k, requestedBytes, xmlComment, _bufSize, 
												 totalFileSize))
							continue;
							if (dataBuf[k+1]=='!') {
											for (; k<requestedBytes; ++k)  {
													if (dataBuf[k] == '>') {
														break;
													}
													if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 3, 
																					totalFileSize)) {
																	cout << "\n\n\t <! ERROR: Incomplete XML document";
													}
											}	
									continue;
							}
										
					if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 1, 
																		totalFileSize)) break;	
					assert (dataBuf[k] == '<');
					//cout << "\n Here --------------- "; 
					if (dataBuf[k+1] == '/') {	
						if (contentAlert && !rElStack.empty()) {
							rElStack.top()->setContent (unitChars, uc);
						}	
						contentAlert 	= false;
						ePopped = rElStack.top();	rElStack.pop();
										//if (ePopped->name != NULL)
										//cout << "\n POPPED out: " << ePopped->name << flush;
						elmAlert = false;
						k++;	// skipping the '/'	
					} else {
								if (!firstTime) {
											if (contentAlert && !rElStack.empty()) {
												rElStack.top()->setContent(unitChars, uc);
											}	
									myElement 	= new XMLelement;
									if (!rElStack.empty())
										 rElStack.top()->childs.push_back (myElement);
									else
										elementList.push_back (myElement);
														
									rElStack.push (myElement);
								} else {
									myElement		= rElStack.top();
									firstTime 		= false;
								}
									elmAlert 		= true;
									contentAlert 	= false;
									
					}
						uc = 0;
				} else if (dataBuf[k] == '=') {
					if (uc > 0) {
						if (elmAlert) {
							bufferedNames.push_back (parser->makeString(unitChars, uc));
							//attValueAlert = true;
							//cout << "\n Added: " << bufferedNames.back() <<"              ";
						}		
					}
					uc = 0;
					
				} else if (dataBuf[k] == '/') {
								
					if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 1, totalFileSize)) 
																						break;
					assert (dataBuf[k] == '/');
						
					if (dataBuf[k+1] == '>') {	
						ePopped = rElStack.top(); rElStack.pop();
						if (uc > 0 && elmAlert) {
							bufferedNames.push_back (parser->makeString (unitChars, uc));
						}
						if (elmAlert)
							myElement->assignAttributes (bufferedNames);
												// if (ePopped->name != NULL)
												// cout << "\n POPPED out: " << ePopped->name << flush;
						elmAlert = false;
						uc = 0;
						k++;
						
					} else {
						unitChars[uc++] = dataBuf[k];	
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
					}
							
					
				} else if (dataBuf[k] == '>') {	
									
					//cout << "\n -------------- WHY am I here again ??   ";			
					
					if (uc > 0 && elmAlert) {
							bufferedNames.push_back (parser->makeString(unitChars, uc));	
					}
					if (elmAlert) 	myElement->assignAttributes (bufferedNames);
					else {
						if (ePopped != NULL) {
							if (uc > 0) {
								eThere = parser->makeString(unitChars, uc);
								//cout <<"\n COMPARING: ["<< ePopped->name << "]--[" << eThere << "]";
								if (strcmp(ePopped->name, eThere)) {
									cout <<"\n\n\t BAD-XML: ["<< ePopped->name << "]--["<<eThere<<"]";
									cout << " Error \n ------ Printing Stack"; 
									while (!rElStack.empty()) {
										rElStack.top()->print();
										rElStack.pop();
									}
									cout << " ERROR \n\n"; 
									exit(0);
								}
								//getchar();
							}
						}
					}
					if (elmAlert) 	contentAlert = true;
					else			contentAlert = false;
					elmAlert = false;
					
					uc = 0;
				} else if (((dataBuf[k] == ' ' || dataBuf[k] == '\t'))) {
					//cout << "\n " << dataBuf << "  >>>>>>>>>>> " << k;
					//cout << "{b}"; 
					//												if (contentAlert) cout << " contentAlert"; 
					//												if (attValueAlert) cout << " attValueAlert";
					if (!contentAlert && !attValueAlert) {		
						if (uc > 0 && elmAlert) {
							bufferedNames.push_back (parser->makeString(unitChars, uc));
							//cout << "\n 1.Added: " << bufferedNames.back() <<"              ";
							//myElement->setName (parser->makeString(unitChars, uc));
							//cout << "\n READING ELE: " << myElement->name <<"  "<< flush;
						}
							uc = 0;
					} else {
						if (!continuousBlanks) {
							//cout << "--------b--------";
							//if (uc > 0)
							unitChars[uc++] = dataBuf[k];
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS;
										}
						}
					}
							continuousBlanks = true;
					
				} else if (dataBuf[k] == '\n') {
									//				if (attValueAlert) cout << " attValueAlert";
						if (!contentAlert && !attValueAlert) {		
								if (uc > 0 && elmAlert) 
								bufferedNames.push_back (parser->makeString(unitChars, uc));
								//cout << "\n 1.Added: " << bufferedNames.back() <<"              ";
								//myElement->setName (parser->makeString(unitChars, uc));
								//cout << "\n READING ELE: " << myElement->name <<"  "<< flush;
								uc = 0;
						}

													if (!elmAlert) {
														if (uc > 0)
																unitChars[uc++] 	= '\n';
													}
													continuousBlanks 	= false;
													
													
				} else if (dataBuf[k] == '%') {	
						if (attValueAlert) {
								unitChars[uc++] = dataBuf[k];	// cout << "*";
						} else {
						//if (dataBuf[k] == '%')  {
							//dataBuf[requestedBytes+1] = '\0';
							//cout << "\n COMMENT: Skipping line: " << dataBuf;
							for (; k<requestedBytes; ++k)  {
								if (dataBuf[k] == '\n') {
									break;
								}
							}	
								if (k==requestedBytes)	continuedComment = true;
				
						//} else 
						//	k--;
						}
									
					
				} else if (dataBuf[k] != '\"') {
						unitChars[uc++] = dataBuf[k];	// cout << "*";
						
										if (uc >= MAXCHARS-10)	{
											char *reAllocArray = new char[2*MAXCHARS];
											memcpy (reAllocArray, unitChars, MAXCHARS*sizeof(char));
											MAXCHARS = 2*MAXCHARS;
											delete [] unitChars;
											unitChars = reAllocArray;
											//cout << "\n Reallocated Memory to: " << MAXCHARS <<" ";
										}
				} else if (dataBuf[k] == '\"') {
						if (attValueAlert)
							attValueAlert = false;
						else {
							attValueAlert = true; 
						}
				}

			//------------------------------------------------------------ 
				
				if (dataBuf[k] != ' ' && dataBuf[k] != '\t') {	
					continuousBlanks = false;
				}	
					
		}// For each char in the line: 	
								
				//	continuousBlanks = false;
	}//--------------------------------------------------------------
			
		//cout << "\n *******************************************************************";
	//	this->print();
		//cout << "\n *******************************************************************" << flush;
		//getchar();
			if (!rElStack.empty()) {
				cout << "\n\n------------------- BAD XML Syntax ";
									while (!rElStack.empty()) {
											rElStack.top()->print();
											rElStack.pop();
									}
				cout << "\n-------------\n"; exit(0);
			}
			 fin.close(); 	fin.clear();
			return true;

}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
			
									





			
			

//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
bool
XMLparser::checkXMLcomment  (char *dataBuf, int & k, int & requestedBytes, bool & xmlComment, 
												int _bufSize, int totalFileSize) {
	bool	parsedComment = false;	
	
	if (xmlComment) {
					 for (; k<requestedBytes; ++k)  {
							if (dataBuf[k] == '-') { 
								if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 3, 
																	totalFileSize)) return true;	
								
								if (dataBuf[k+1] == '-') 
								if (dataBuf[k+2] == '>') {
									xmlComment = false; k += 3; // To parse it off. 
									break;
								}
							}
						}
					return true;
	} //-+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ -+ 
	
		if (dataBuf[k] != '<') return false;

			if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 3, 
																totalFileSize)) return false;
					if (dataBuf[k+1]=='!') 
					if (dataBuf[k+2]=='-')
					if (dataBuf[k+3]=='-') {
															xmlComment = true;
															parsedComment = true;
						for (; k<requestedBytes; ++k)  {
							if (dataBuf[k] == '-') { 
								if (!assertFullBuffer (dataBuf, k, requestedBytes, _bufSize, 3, 
																	totalFileSize)) return true;	
								
								if (dataBuf[k+1] == '-') 
								if (dataBuf[k+2] == '>') {
									xmlComment = false;
									//cout << "\n Also ended it ";
									k = k+2;
									break;
								}
							}
						//	cout << "\n requestedBytes: " << requestedBytes << " _bufSize " 
						//		<< _bufSize << " totalFileSize " << totalFileSize << " k: " << k;
							//cout << "  ";
							//for (int i=0; i<k; ++i)
							//	cout << dataBuf[i];
						}
					}
								//if (parsedComment) {
												//cout << "\n Found an XML comment ";  getchar();
												//assert (1==2);
								//}
		return parsedComment;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!
			
			









//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Notes: 
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
bool
XMLparser::assertFullBuffer (char *dataBuf, int & cIndex, int & requestedBytes, int _bufSize, 
																		int lookAhead, 
																		int totalFileSize) {
	
	//cout << "\n Asserting Full Buffer: ";
	if (cIndex + lookAhead < requestedBytes)  {
					//cout << "  [Yes] ";
					return true;
	}
	
		 int 	   offset	= (cIndex - requestedBytes);	//Logic Changed on 24-Aug'06
		 //int 	   offset	= (cIndex - _bufSize);
		fin.seekg (offset, ios::cur);	assert (fin.good());
		
		long int	bytesLeft;  pCurrentPos = fin.tellg();
						
					requestedBytes = ((bytesLeft=totalFileSize-pCurrentPos) > _bufSize) ? 
																		_bufSize : bytesLeft;
					
		//cout << "\n\n\n ------------------------------REFILLING: " << requestedBytes <<"  "<< flush;
					
					if (requestedBytes == 0) 	return false;
							
		fin.read ((char*)dataBuf, requestedBytes);
					
					cIndex = 0;
																	return true;
}//!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!_!


