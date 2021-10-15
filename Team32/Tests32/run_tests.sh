#!/bin/bash

SCRIPT_PATH="${0%/*}"

echo $0;

if [[ $# -ne 1 ]]; then
    echo "Expected arguments: <PATH_TO_AUTOTESTER_BINARIES>";
    exit 1;
fi

AUTOTESTER_PATH="$(cd "$(dirname "$1")"; pwd)/$(basename "$1")"
total_failed=0

pushd $SCRIPT_PATH;
echo "";

declare -a testsuites=(
    "./base/without_clause/without_clause_"
    "./base/single_clause/modifies/one_synonym_"
    "./base/single_clause/modifies/two_synonym_"
    "./base/single_clause/uses/one_synonym_"
    "./base/single_clause/uses/two_synonym_"
    "./base/single_clause/parent/one_synonym_"
    "./base/single_clause/parent/two_synonym_"
    "./base/single_clause/parent_star/one_synonym_"
    "./base/single_clause/parent_star/two_synonym_"
    "./base/single_clause/follows/one_synonym_"
    "./base/single_clause/follows/two_synonym_"
    "./base/single_clause/follows_star/one_synonym_"
    "./base/single_clause/follows_star/two_synonym_"
    "./base/single_clause/pattern/assign/subtree_match_"
    "./base/single_clause/pattern/assign/full_match_"
    "./base/double_clause/follows_pattern/"
    "./base/double_clause/follows_star_pattern/"
    "./base/double_clause/parent_pattern/"
    "./base/double_clause/parent_star_pattern/"
    "./base/double_clause/modifies_pattern/"
    "./base/double_clause/uses_pattern/"
    "./base/errors/semantic/"
    "./base/errors/syntactic/"
    "./non_nested_"
    "./nested_"
    "./multi_nested_"
);

for i in "${testsuites[@]}";
do
    OUTPUT=$($AUTOTESTER_PATH "${i}source.txt" "${i}queries.txt" "${i}output.xml");

    OOPSIES=$?
    MISSING=$(echo "$OUTPUT" | grep "Missing:")
    ADDITIONAL=$(echo "$OUTPUT" | grep "Additional:")

    if [[ ! -z "$MISSING" && ! -z "$ADDITIONAL" ]]
    then
        echo "${i}queries.txt failed!";

        ((total_failed++));
    fi

    if [[ "$OOPSIES" -ne 0 ]]
    then
        echo "${i}source.txt failed parsing!";

        ((total_failed++));
    fi
done

echo "";
popd;

if [[ total_failed -ne 0 ]]
then
    exit 1;
fi

