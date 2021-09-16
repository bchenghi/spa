#!/bin/bash

SCRIPT_PATH="${0%/*}"

echo $0;

if [[ $# -ne 1 ]]; then
    echo "Expected arguments: <PATH_TO_AUTOTESTER_BINARIES>";
    exit;
fi

AUTOTESTER_PATH="$(cd "$(dirname "$1")"; pwd)/$(basename "$1")"

pushd $SCRIPT_PATH;

$AUTOTESTER_PATH ./base/without_clause/without_clause_source.txt ./base/without_clause/without_clause_queries.txt ./base/without_clause/without_clause_output.xml;
$AUTOTESTER_PATH ./base/single_clause/modifies/one_synonym_source.txt ./base/single_clause/modifies/one_synonym_queries.txt ./base/single_clause/modifies/one_synonym_output.xml;
$AUTOTESTER_PATH ./base/single_clause/uses/one_synonym_source.txt ./base/single_clause/uses/one_synonym_queries.txt ./base/single_clause/uses/one_synonym_output.xml;
$AUTOTESTER_PATH ./base/single_clause/parent/one_synonym_source.txt ./base/single_clause/parent/one_synonym_queries.txt ./base/single_clause/parent/one_synonym_output.xml;
$AUTOTESTER_PATH ./base/single_clause/parent_star/one_synonym_source.txt ./base/single_clause/parent_star/one_synonym_queries.txt ./base/single_clause/parent_star/one_synonym_output.xml;
$AUTOTESTER_PATH ./base/single_clause/follows/one_synonym_source.txt ./base/single_clause/follows/one_synonym_queries.txt ./base/single_clause/follows/one_synonym_output.xml;
$AUTOTESTER_PATH ./base/single_clause/follows_star/one_synonym_source.txt ./base/single_clause/follows_star/one_synonym_queries.txt ./base/single_clause/follows_star/one_synonym_output.xml;

popd;

