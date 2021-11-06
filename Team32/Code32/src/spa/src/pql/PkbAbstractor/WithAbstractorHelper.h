#ifndef GUARD_WITH_ABSTRACTOR_HELPER_H
#define GUARD_WITH_ABSTRACTOR_HELPER_H

namespace pql {
    class WithAbstractorHelper {
    public:
        static list<pair<Value, Value>> getWithNoneValues(DesignEntity, AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithOneValueLeft(DesignEntity, AttributeType, const Value& value2);
        static list<pair<Value, Value>> getWithOneValueRight(DesignEntity, AttributeType, const Value& value2);
        static list<pair<Value, Value>> getWithBothValues(const Value& value1, const Value& value2);

    private:
        static list<pair<Value, Value>> getWithNoneValuesHelperAssign1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperCall1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperConstant1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperIf1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperPrint1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperProcedure1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperStmtOrProgline1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperRead1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperVariable1(AttributeType, DesignEntity, AttributeType);
        static list<pair<Value, Value>> getWithNoneValuesHelperWhile1(AttributeType, DesignEntity, AttributeType);
    };
}

#endif //GUARD_WITH_ABSTRACTOR_HELPER_H
