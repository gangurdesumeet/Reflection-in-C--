#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "Emitter.hpp"

using namespace std;



/*
 * These are the type codes:
 *   _135: void
 *   _126: int
 *   _139: const char *
 */

/*
 * Simple example to parse a file given as a single argument, walk
 * down the DOM, and emit a file named after the input file name.
 */

void print_element_names(xmlNode *, Emitter &, Emitter &);

string base_name(const std::string &fn);

int
main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: ./cg_xml input_xml_file\n");
        exit(1);
    }

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    /*
     * This initializes the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    // Probably will not actually need anything in the .hpp file.
    string bn = base_name(argv[1]) + "_meta";

    ofstream hpp_file((bn + ".hpp").c_str());
    assert(hpp_file.good());
    Emitter hpp_emitter(&hpp_file);
    hpp_emitter.emitLine("/*  This file is generated.  DO NOT MODIFY DIRECTLY!  */");
    hpp_emitter.emitLine("");

    ofstream cpp_file((bn + ".cpp").c_str());
    assert(cpp_file.good());
    Emitter cpp_emitter(&cpp_file);
    cpp_emitter.emitLine("/*  This file is generated.  DO NOT MODIFY DIRECTLY!  */");
    cpp_emitter.emitLine("");

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element, hpp_emitter, cpp_emitter);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return 0;
}

void
print_element_names(xmlNode *a_node, Emitter &hpp_em, Emitter &cpp_em) {

    xmlNode *cur_node = NULL;
    xmlAttr * aptr;
	
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
		
            // Look for elements named "Class".
            if (!strcmp((const char *) cur_node->name, "Class")) {
                printf("Class Name: ");
                // The name of the class is in the attribute named
                // "name", so look through the attributes.
                aptr = cur_node->properties;
                while (aptr) {			    
                    if (!strcmp((const char *) aptr->name, "name")) {
                        // The value of the attribute is here.
                        const string class_name((const char *) aptr->children->content);
                        printf("%s\n", class_name.c_str());
                        // Make $$ in the emitted text get replaced
                        // with the class name, for convenience.
                        cpp_em.setReplacement(class_name + "_meta");
                        cpp_em.emitLine("#include \"MetaInfo.hpp\"");
                        cpp_em.emitLine("#include <assert.h>");
                        cpp_em.emitLine("#include <iostream>");
                        cpp_em.emitLine("#include <string>");
                        cpp_em.emitLine("");
                        cpp_em.emitLine("using namespace std;");
                        cpp_em.emitLine("using namespace cs540;");
                        cpp_em.emitLine("");
                        cpp_em.emitLine("class $$ : public MetaInfo {");
                        cpp_em.emitLine(1, "public:");
                        cpp_em.emitLine(1, "virtual string className() const;");
                        cpp_em.emitLine(-2, "};");
                        cpp_em.emitLine("");
                        cpp_em.emitLine("string");
                        cpp_em.emitLine("$$::className() const {");
                        cpp_em.increment_indent_level();
                        for (int i = 0; i < 10; i++) {
                            // Shows use of formatted emit.
                            cpp_em.emitLineF("cout << %d << endl;", i);
                        }
                        cpp_em.emitLine("return \"$$\";");
                        cpp_em.emitLine(-1, "}");
                        cpp_em.emitLine("");
                        cpp_em.emitLine("namespace {");
                        cpp_em.emitLine(1, "$$ m;");
                        cpp_em.emitLine(-1, "}");
                        cpp_em.emitLine("");
                    }
                    aptr = aptr->next;
                }
                printf("Fields\n");			  
            }
		
            // Look for elements named Method.
            if (!strcmp((const char *) cur_node->name, "Method")) {
                printf("Method Name: ");
                // The return type is in an attribute.
                aptr = cur_node->properties;
                while (aptr) {
                    if (!strcmp((const char *) aptr->name, "returns")) {
                        printf("Returns: ");
                        printf("%s\n",aptr->children->content);
                    }
                    // The name of the method is also an attribute.
                    if (!strcmp((const char *) aptr->name,"name")) {
                        printf("%s\n",aptr->children->content);
                        cpp_em.emitLineF("/* Method: %s */", aptr->children->content);
                    }
                    aptr = aptr->next;
                }
                printf("Method Arguments\n");			  
            }			  
			
            // Method Arguments		   
            if (!strcmp((const char *) cur_node->name,"Argument") &&
             !strcmp((const char *) cur_node->parent->name,"Method")) {
                // The name and type are both attributes.
                aptr = cur_node->properties;
                while (aptr) {
                    if (!strcmp((const char *) aptr->name,"name")) {
                        printf("Name: ");
                        printf("%s\n",aptr->children->content);				  
                    }
                    if (!strcmp((const char *) aptr->name,"type")) {
                        printf("Type: ");
                        printf("%s\n",aptr->children->content);				  
                    }
                    aptr = aptr->next;
                }	
            }

        }		
        print_element_names(cur_node->children, hpp_em, cpp_em);
    }
}

string
base_name(const std::string &fn) {
    string base = fn;
    // Search for . to find the file extension.
    string::size_type pos = base.find('.');
    if (pos == string::npos) {
        fprintf(stderr, "File name %s not in right form.\n", base.c_str());
        exit(1);
    }
    // Truncate the file extension.
    base.erase(pos);
    cerr << "base: " << base << endl;
    return base;
}
