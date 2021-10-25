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
    "./base/single_clause/affects/one_synonym_"
    "./base/single_clause/affects/two_synonym_"
    "./base/single_clause/affects_star/one_synonym_"
    "./base/single_clause/affects_star/two_synonym_"
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
    "./base/single_clause/calls/one_synonym_"
    "./base/single_clause/calls/two_synonym_"
    "./base/single_clause/calls_star/one_synonym_"
    "./base/single_clause/calls_star/two_synonym_"
    "./base/single_clause/next/one_synonym_"
    "./base/single_clause/next/two_synonym_"
    "./base/single_clause/next_star/one_synonym_"
    "./base/single_clause/next_star/two_synonym_"
    "./base/single_clause/pattern/assign/subtree_match_"
    "./base/single_clause/pattern/assign/full_match_"
    "./base/single_clause/pattern/if/"
    "./base/single_clause/pattern/while/"
    # "./base/single_clause/with/no_synonym_"
    # "./base/single_clause/with/one_synonym_"
    # "./base/single_clause/with/two_synonym_"
    "./base/double_clause/affects/"
    "./base/double_clause/affects_star/"
    "./base/double_clause/calls/"
    "./base/double_clause/calls_star/"
    "./base/double_clause/follows/"
    "./base/double_clause/follows_star/"
    "./base/double_clause/parent/"
    "./base/double_clause/parent_star/"
    "./base/double_clause/modifies/"
    "./base/double_clause/uses/"
    # "./base/double_clause/with/"
    "./base/errors/semantic/"
    "./base/errors/syntactic/"
    "./demo/source1/single_clause_"
    "./demo/source1/multiple_clause_no_common_"
    "./demo/source1/multiple_clause_common_"
    "./demo/source2/single_clause_"
    "./demo/source2/multiple_clause_no_common_"
    "./demo/source2/multiple_clause_common_"
    "./demo/source3/single_clause_"
    "./demo/source3/multiple_clause_no_common_"
    "./demo/source3/multiple_clause_common_"
    "./non_nested_"
    "./nested_"
    "./multi_nested_"
    "./edge_cases/keywords/"
    "./edge_cases/single_line/"
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
        echo "${i}source.txt either failed parsing or timed out!";

        ((total_failed++));
    fi
done

echo "";
popd;

if [[ total_failed -ne 0 ]]
then
    exit 1;
fi

