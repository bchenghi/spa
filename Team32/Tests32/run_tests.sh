#!/bin/bash

SCRIPT_PATH="${0%/*}"

echo $0;

if [[ $# -ne 1 ]]; then
    echo "Expected arguments: <PATH_TO_AUTOTESTER_BINARIES>";
    exit;
fi

AUTOTESTER_PATH="$(cd "$(dirname "$1")"; pwd)/$(basename "$1")"

pushd $SCRIPT_PATH;

declare -a testcases=(
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
    "./base/single_clause/pattern/assign/full_match_"
    "./base/single_clause/pattern/assign/subtree_match_"
);

for i in "${testcases[@]}";
do
    $AUTOTESTER_PATH "${i}source.txt" "${i}queries.txt" "${i}output.xml";
done

popd;

