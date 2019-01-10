#pragma once
#include <dataObject/DataObject.h>
#include <dataObject/Exception.h>
#include <string>
#include <vector>

namespace dataobject
{
/*
 * {
  "type": "string",
  "enum": ["0x0"]
}
{
   "type": "string"
}
*/


/// Validation scheme datastructure
class DataObjectScheme
{
public:
    // Initialize scheme from description
    DataObjectScheme(DataObject const& _init) { readRules(_init); }

    class ValidationRule
    {
    public:
        enum class verification
        {
            CHECK_EXACT,
            CHECK_TYPE
        };
        DataType dataTypeExpected;
        verification verificationType;
        DataObject dataEnum;
    };

    std::vector<ValidationRule> const& getRules() { return rulesVector; }

private:
    void readRules(DataObject const& _obj)
    {
        if (_obj.type() != DataType::Object)
            throw DataObjectException()
                << "Validation scheme object is expected to be of object type(1)!";
        if (!_obj.count("type"))
            throw DataObjectException() << "Required field 'type' not found in validation scheme!";
        if (_obj.at("type").type() != DataType::String)
            throw DataObjectException()
                << "Validation scheme 'type' field must be a string object!";

        ValidationRule rule;
        // Read string field (data type) into DataObject type
        rule.verificationType = ValidationRule::verification::CHECK_TYPE;
        if (_obj.at("type").asString() == "string")
            rule.dataTypeExpected = DataType::String;
        else if (_obj.at("type").asString() == "integer")
            rule.dataTypeExpected = DataType::Integer;


        // validation scheme has enum field
        if (_obj.count("enum"))
        {
            if (_obj.at("enum").type() != DataType::Array)
                throw DataObjectException() << "Validation scheme 'enum' field must be an array!";
            rule.verificationType = ValidationRule::verification::CHECK_EXACT;
            rule.dataEnum = _obj.at("enum").getSubObjects().at(0);
        }

        rulesVector.push_back(rule);
    }

private:
    std::vector<ValidationRule> rulesVector;
};
}
