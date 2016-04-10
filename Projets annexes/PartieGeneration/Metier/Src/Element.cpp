#include "../Include/Element.h"
#include "../Include/Module.h"

using namespace std;


Element::Element() : m_id(""), m_elementName(""), m_content("") {}

Element::Element(string moduleName) : m_moduleName(moduleName), m_content("")
{
    moduleToElement(*this);
    m_id = generateId(m_elementName);
}

Element::Element(string moduleName, string content) : m_moduleName(moduleName)
{
    moduleToElement(*this);
    this->m_content=content;
    m_id = generateId(m_elementName);
}

Element::~Element() {}

//Getters and Setters
string Element::getId() const {return m_id;}
string Element::getElementName() const {return m_elementName;}
string Element::getContent() const {return m_content;}
string Element::getModuleName() const {return m_moduleName;}

void Element::setContent(string content) {this->m_content=content;}
void Element::setElementName(string elementName) {this->m_elementName=elementName;}
void Element::setId(string id) {this->m_id=id;}


//Getters for map elements
string Element::getAttribute(string attributeName)
{
    string attribute = m_attributes[attributeName];
    if(attribute != "")
        return attribute;
    cout << "This attribute doesn't exist in the attributes map!" <<endl;
    return NULL;
}

string Element::getStyle(string styleName)
{
    string style = m_styles[styleName];
    if(style != "")
        return style;
    cout << "This style doesn't exist in the styles map!" <<endl;
    return NULL;
}

//Setters for map elements
void Element::setAttribute(string attributeName, string attribute)
{
    m_attributes[attributeName] = attribute;
}

void Element::setStyle(string styleName , string style)
{
    m_styles[styleName] = style;
}

void Element::addElement(Element e)
{
    m_childElements.push_back(e);
}

Element* Element::getElement(unsigned int i)
{
    return &m_childElements[i];
}

void Element::removeElement(unsigned int i)
{
    if(i<m_childElements.size())
    {
        m_childElements.erase(m_childElements.begin()+i);
    }
}

unsigned int Element::nbElement()
{
    return m_childElements.size();
}

string Element::toString() const
{
    string res="";
    if(m_elementName=="textException")
    {
        res+=m_content;
    }
    else {
        res+="<"+m_elementName+" id = \""+m_id+"\">";
        res+=m_content;
        for(unsigned int i=0;i<m_childElements.size();i++)
        {
            res+="\n\t";
            res+=m_childElements[i].toString();
        }
        res+="</"+m_elementName+">\n";
    }
    return res;
}

string Element::toJson()
{
    string res="\t\t\t\t\t{ \"element\" : {\n";
    res+="\t\t\t\t\t\t\"type\" : \""+m_elementName+"\",\n";
    res+="\t\t\t\t\t\t\"id\" : \""+m_id+"\",\n";
    res+="\t\t\t\t\t\t\"attributes\" : [";
    for(map<string,string>::iterator i=m_attributes.begin();i!=m_attributes.end();i++)
    {
        if(i!=m_attributes.begin())
        {
            res+=", ";
        }
        res+="{ \"attribute\" : \""+i->first+"\", \"value\" : \""+i->second+"\"}";
    }
    res+="],\n";
    res+="\t\t\t\t\t\t\"style\" : [";
    for(map<string,string>::iterator i=m_styles.begin();i!=m_styles.end();i++)
    {
        if(i!=m_styles.begin())
        {
            res+=", ";
        }
        res+="{ \"style\" : \""+i->first+"\", \"value\" : \""+i->second+"\"}";
    }
    res+="],\n";
    res+="\t\t\t\t\t\t\"texte\" : \""+m_content+"\",\n";
    res+="\t\t\t\t\t\t\"content\" : [";
    for(unsigned int i=0;i<m_childElements.size();i++)
    {
        if(i!=0)
        {
            res+=",\n";
        }
        res+=m_childElements[i].toJson();
    }
    res+="]\n";
    res+="\t\t\t\t\t}}\n";
    return res;
}
