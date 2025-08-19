#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Abstraction for document elements
class  DocumentElement {
public:
    virtual string render() = 0;

};

class TextElement : public DocumentElement {
    private :
        string text;
    public:
        TextElement(string text) {
            this->text = text;
        }

        string render () override {
            return text;
        }
};

class ImageElement : public DocumentElement {
    private :
        string imagePath;
    public:
        ImageElement(string imagePath) {
            this->imagePath = imagePath;
        }

        string render () override {
            return "[Image: " + imagePath + "]";
        }
};

//NewLineElement represents a line break in the document
class NewLineElement : public DocumentElement {
    public:
        string render() override {
            return "\n";
        }
};

//TabSpaceElement represents a tab space in the document
class TabSpaceElement : public DocumentElement {
    public:
        string render() override {
            return "\t";
        }
};

// Document class is responsibke for holding a collection of elements
class Document {
    private :
        vector<DocumentElement*> documentElements;

    public: 
        void addElement(DocumentElement* element){
            documentElements.push_back(element);
        }

        //Render the document by concatenating the render output of all elements.
        string render() {
            string result;
            for( auto element: documentElements) {
                result += element->render();
            }
            return result;
        }
};

//Persistence Interface
class Persistence {
public:
    virtual void save(string data) = 0;
};


class FileStorage : public Persistence {
public:
     void save( string data) override {
        ofstream outFile("document.txt");
        if (outFile) {
            outFile << data;
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
     }
};

class DBStorage : public Persistence {
public:
     void save( string data) override {
        //save to db
     }
};

class DocumentEditor1
{
private:
    /* data */
    Document* document;
    Persistence* storage;
    string renderedDocument;

public:
    DocumentEditor1(Document* document, Persistence* storage) {
        this->document = document;
        this->storage = storage;
    };

    //Adds text as a plain string
    void addText( string text) {
        document->addElement(new TextElement(text));
    }

    //Adds an image represented by its file path
    void addImage( string imagePath) {
        document->addElement(new ImageElement(imagePath));
    }

    //Adds new line to the document
    void addNewLine() {
        document->addElement(new NewLineElement());
    }

    //Adds tab space to the document
    void addTabSpace() {
        document->addElement(new TabSpaceElement());
    }

    string renderDocument() {
        if(renderedDocument.empty()) {
            renderedDocument = document->render();
        }

        return renderedDocument;
    }

    void saveDocument() {
        storage->save(renderDocument());
    }
    
};

int main() {
    Document* document = new Document();
    Persistence* persistence = new FileStorage();

    DocumentEditor1* editor = new DocumentEditor1(document, persistence);

    //Simulate a client using the editor with common text formatting features.
    editor->addText("Hello, world!");
    editor->addNewLine();
    editor->addText("This is areal world document editor example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Intended text after a tab space");
    editor->addNewLine();
    editor->addImage("picture.jpg");

    // Render and display the final document.
    cout << editor->renderDocument() << endl;

    editor->saveDocument();

    return 0;
}





