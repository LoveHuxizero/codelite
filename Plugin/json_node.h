#ifndef ZJSONNODE_H
#define ZJSONNODE_H

#include <wx/string.h>
#include <wx/variant.h>
#include <wx/filename.h>
#include <wx/arrstr.h>
#include "codelite_exports.h"
#include "cJSON.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_SDK JSONElement
{
protected:
    cJSON * _json;
    int     _type;
    wxString _name;

    // Values
    wxVariant _value;

public:
    JSONElement(cJSON *json);
    JSONElement(const wxString &name, const wxVariant& val, int type);
    
    virtual ~JSONElement() {}

    // Setters
    ////////////////////////////////////////////////
    void setName(const wxString& _name) {
        this->_name = _name;
    }
    void setType(int _type) {
        this->_type = _type;
    }
    int getType() const {
        return _type;
    }
    const wxString& getName() const {
        return _name;
    }
    const wxVariant& getValue() const {
        return _value;
    }
    void setValue(const wxVariant& _value) {
        this->_value = _value;
    }
    // Readers
    ////////////////////////////////////////////////
    JSONElement   namedObject(const wxString& name) const ;
	bool          hasNamedObject(const wxString &name) const;
    bool          toBool()           const ;
    wxString      toString()         const ;
    wxArrayString toArrayString()    const ;
    JSONElement   arrayItem(int pos) const ;
    bool          isNull()           const ;
    bool          isBool()           const ;
    wxString      format()           const ;
    int           arraySize()        const ;
    int           toInt(int defaultVal = -1) const ;
    double        toDouble(double defaultVal = -1.0) const;

    // Writers
    ////////////////////////////////////////////////
    /**
     * @brief create new named object and append it to this json element
     * @return the newly created object
     */
    static JSONElement createObject(const wxString &name = wxT(""));
    /**
     * @brief create new named array and append it to this json element
     * @return the newly created array
     */
    static JSONElement createArray(const wxString &name = wxT(""));

    /**
     * @brief append new element to this json element
     */
    void append(const JSONElement& element);
    
    /**
     * @brief add string property to a JSON object
     */
    JSONElement& addProperty(const wxString &name, const wxString &value);
    JSONElement& addProperty(const wxString& name, const wxChar* value);
    
    /**
     * @brief add int property to a JSON object
     */
    JSONElement& addProperty(const wxString &name, int value);

    /**
     * @brief add boolean property to a JSON object
     */
    JSONElement& addProperty(const wxString &name, bool value);
    
    /**
     * @brief add wxArrayString property 
     */
    JSONElement& addProperty(const wxString &name, const wxArrayString &arr);
    
    //////////////////////////////////////////////////
    // Array operations
    //////////////////////////////////////////////////

    /**
     * @brief append new number
     * @return the newly added property
     */
    void arrayAppend(const JSONElement& element) ;;
    void arrayAppend(const wxString &value);

    bool isOk() const {
        return _json != NULL;
    }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_SDK JSONRoot
{
    cJSON *_json;
    wxString _errorString;

public:
    JSONRoot(int type);
    JSONRoot(const wxString& text);
    JSONRoot(const wxFileName& filename);
    virtual ~JSONRoot();
    
    void save(const wxFileName &fn);
    wxString errorString() const;
    bool isOk() const {
        return _json != NULL;
    }

    JSONElement toElement() const ;;

    void clear();

private:
    // Make this class not copyable
    JSONRoot(const JSONRoot& src);
    JSONRoot& operator=(const JSONRoot& src);
};


#endif // ZJSONNODE_H