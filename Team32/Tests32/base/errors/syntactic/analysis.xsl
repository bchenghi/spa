<?xml-stylesheet type="text/xsl" href="analysis.xsl"?>
<test_results>
<info>
<name>autotester</name><parsing_time_taken>17.394000</parsing_time_taken>
</info>
<queries>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Underscore only at the front [assignment_pattern_args_invalid_queries]">1</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows("a", s) pattern a(_, _"1")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>5.864000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Underscore only at the back [assignment_pattern_args_invalid_queries]">2</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows(s, "a") pattern a(_, "1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.236000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Missing quotes [assignment_pattern_args_invalid_queries]">3</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows(s, "a") pattern a(_, _1_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.108000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Number as argument for LHS [assignment_pattern_args_invalid_queries]">4</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows(s, "a") pattern a(1, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.574000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="Invalid expression for assign pattern [assign_pattern_expr_invalid]">5</id><querystr><![CDATA[assign a, a1; variable v; Select a1 pattern a(v, _"a x b"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.163000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="Invalid expression for assign pattern [assign_pattern_expr_invalid]">6</id><querystr><![CDATA[assign a, a1; variable v; Select a1 pattern a(v, _"(a + b) / c )"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.779000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as first arg in Follows [follows_parent_string_argument_queries]">7</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.424000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as second arg in Follows [follows_parent_string_argument_queries]">8</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.989000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as first arg in Follows Star [follows_parent_string_argument_queries]">9</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows*("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.132000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as second arg in Follows Star [follows_parent_string_argument_queries]">10</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows*(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.445000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as first arg in Parent [follows_parent_string_argument_queries]">11</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Parent("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.127000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as second arg in Parent [follows_parent_string_argument_queries]">12</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Parent(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.243000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as first arg in Parent Star [follows_parent_string_argument_queries]">13</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Parent*("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.568000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as second arg in Parent Star [follows_parent_string_argument_queries]">14</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Parent*(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.455000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Missing semicolon [missing_items_queries]">15</id><querystr><![CDATA[assign a; stmt s constant c; Select s such that Follows("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.787000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Missing design entity [missing_items_queries]">16</id><querystr><![CDATA[assign a; s; constant c; Select s such that Follows(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.582000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="Missing such that [missing_items_queries]">17</id><querystr><![CDATA[assign a; stmt s; constant c; Select s Follow*("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.741000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Missing bracket [missing_items_queries]">18</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows*(s, "a") pattern a_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.659000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Modifies="1" SuchThat="1" CondNum="3" RelNum="1" comment="String as first arg for Modifies [modifies_uses_first_arg_num]">19</id><querystr><![CDATA[variable v; stmt s, s1; constant c; Select v such that Modifies("1", v)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.537000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Uses="1" SuchThat="1" CondNum="3" RelNum="1" comment="String as first arg for Uses [modifies_uses_first_arg_num]">20</id><querystr><![CDATA[variable v; stmt s, s1; constant c; Select v such that Uses("1", v)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.612000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Design entity spelling [spelling_errors_queries]">21</id><querystr><![CDATA[assign a; stmt s; const c; Select s such that Follows("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.290000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Select clause name spelling [spelling_errors_queries]">22</id><querystr><![CDATA[assign a; stmt s; constant c; Selet s such that Follows(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.456000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="Such that clause spelling [spelling_errors_queries]">23</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follow*("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.243000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="Pattern clause spelling [spelling_errors_queries]">24</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows*(s, "a") patten a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.419000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Modifies clause [string_not_alphanumeric]">25</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Modifies(s, "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.485000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Modifies clause [string_not_alphanumeric]">26</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Modifies(s, ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.715000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Modifies clause [string_not_alphanumeric]">27</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Modifies(s, ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.865000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Modifies clause [string_not_alphanumeric]">28</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Modifies(s, " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.198000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Modifies clause [string_not_alphanumeric]">29</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Modifies(s, "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.380000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Modifies clause [string_not_alphanumeric]">30</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Modifies(s, "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.569000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Modifies clause [string_not_alphanumeric]">31</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Modifies(s, "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.567000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Uses="1" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Uses clause [string_not_alphanumeric]">32</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Uses(s, "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.448000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Uses clause [string_not_alphanumeric]">33</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Uses(s, ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.338000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Uses clause [string_not_alphanumeric]">34</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Uses(s, ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.229000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Uses clause [string_not_alphanumeric]">35</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Uses(s, " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.283000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Uses clause [string_not_alphanumeric]">36</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Uses(s, "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.647000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Uses clause [string_not_alphanumeric]">37</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Uses(s, "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.574000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Uses clause [string_not_alphanumeric]">38</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Uses(s, "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.816000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="_ in pattern a clause [string_not_alphanumeric]">39</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern a("_", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.766000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment=", in pattern a clause [string_not_alphanumeric]">40</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern a(",", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.112000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment=". in pattern a clause [string_not_alphanumeric]">41</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern a(".", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.593000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="in pattern a clause [string_not_alphanumeric]">42</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern a(" ", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.729000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="in pattern a clause [string_not_alphanumeric]">43</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern a("", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.131000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="/ in pattern a clause [string_not_alphanumeric]">44</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern a("/", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.638000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="a-b in pattern a clause [string_not_alphanumeric]">45</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern a("a-b", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.067000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="4" Pattern="1" SuchThat="1" CondNum="7" RelNum="0" comment="_ in pattern i clause [string_not_alphanumeric]">46</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern i("_", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.704000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment=", in pattern i clause [string_not_alphanumeric]">47</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern i(",", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.511000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment=". in pattern i clause [string_not_alphanumeric]">48</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern i(".", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.490000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="in pattern i clause [string_not_alphanumeric]">49</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern i(" ", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.632000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="in pattern i clause [string_not_alphanumeric]">50</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern i("", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.703000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="/ in pattern i clause [string_not_alphanumeric]">51</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern i("/", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.192000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="a-b in pattern i clause [string_not_alphanumeric]">52</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern i("a-b", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.577000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="_ in pattern w clause [string_not_alphanumeric]">53</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern w("_", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.903000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment=", in pattern w clause [string_not_alphanumeric]">54</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern w(",", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.792000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment=". in pattern w clause [string_not_alphanumeric]">55</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern w(".", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.705000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="in pattern w clause [string_not_alphanumeric]">56</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern w(" ", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.273000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="in pattern w clause [string_not_alphanumeric]">57</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern w("", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.285000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="/ in pattern w clause [string_not_alphanumeric]">58</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern w("/", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.166000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="a-b in pattern w clause [string_not_alphanumeric]">59</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that pattern w("a-b", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.351000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Calls clause on LHS [string_not_alphanumeric]">60</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("_", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.743000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Calls clause on RHS [string_not_alphanumeric]">61</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("abc", "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.618000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="3" SuchThat="1" CondNum="6" RelNum="1" comment="_ in Calls clause on both sides [string_not_alphanumeric]">62</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("_", "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.710000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls clause on LHS [string_not_alphanumeric]">63</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls(",", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.953000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls clause on RHS [string_not_alphanumeric]">64</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("abc", ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.666000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls clause on both sides [string_not_alphanumeric]">65</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls(",", ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.934000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls clause on LHS [string_not_alphanumeric]">66</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls(".", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.735000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls clause on RHS [string_not_alphanumeric]">67</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("abc", ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.516000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls clause on both sides [string_not_alphanumeric]">68</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls(".", ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.994000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on LHS [string_not_alphanumeric]">69</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls(" ", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.621000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on RHS [string_not_alphanumeric]">70</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("abc", " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.935000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on both sides [string_not_alphanumeric]">71</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls(" ", " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.638000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on LHS [string_not_alphanumeric]">72</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.935000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on RHS [string_not_alphanumeric]">73</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("abc", "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.735000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on both sides [string_not_alphanumeric]">74</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("", "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.884000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls clause on LHS [string_not_alphanumeric]">75</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("/", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.889000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls clause on RHS [string_not_alphanumeric]">76</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("abc", "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.867000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls clause on both sides [string_not_alphanumeric]">77</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("/", "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.530000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls clause on LHS [string_not_alphanumeric]">78</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("a-b", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.595000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls clause on RHS [string_not_alphanumeric]">79</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("abc", "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.822000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls clause on both sides [string_not_alphanumeric]">80</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls("a-b", "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.606000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Calls* clause on LHS [string_not_alphanumeric]">81</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("_", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.828000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Calls* clause on RHS [string_not_alphanumeric]">82</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("abc", "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.385000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="3" SuchThat="1" CondNum="6" RelNum="1" comment="_ in Calls* clause on both sides [string_not_alphanumeric]">83</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("_", "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.329000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls* clause on LHS [string_not_alphanumeric]">84</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*(",", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.120000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls* clause on RHS [string_not_alphanumeric]">85</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("abc", ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.761000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls* clause on both sides [string_not_alphanumeric]">86</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*(",", ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.446000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls* clause on LHS [string_not_alphanumeric]">87</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*(".", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.714000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls* clause on RHS [string_not_alphanumeric]">88</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("abc", ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.416000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls* clause on both sides [string_not_alphanumeric]">89</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*(".", ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.608000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on LHS [string_not_alphanumeric]">90</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*(" ", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.026000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on RHS [string_not_alphanumeric]">91</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("abc", " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.803000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on both sides [string_not_alphanumeric]">92</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*(" ", " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.762000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on LHS [string_not_alphanumeric]">93</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.890000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on RHS [string_not_alphanumeric]">94</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("abc", "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.866000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on both sides [string_not_alphanumeric]">95</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("", "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.530000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls* clause on LHS [string_not_alphanumeric]">96</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("/", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.677000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls* clause on RHS [string_not_alphanumeric]">97</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("abc", "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.194000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls* clause on both sides [string_not_alphanumeric]">98</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("/", "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.473000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls* clause on LHS [string_not_alphanumeric]">99</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("a-b", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.584000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls* clause on RHS [string_not_alphanumeric]">100</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("abc", "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.390000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls* clause on both sides [string_not_alphanumeric]">101</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select s such that Calls*("a-b", "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.235000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Underscore only at the front [assignment_pattern_args_invalid_queries]">102</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows("a", s) pattern a(_, _"1")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.152000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Underscore only at the back [assignment_pattern_args_invalid_queries]">103</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows(s, "a") pattern a(_, "1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.221000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Missing quotes [assignment_pattern_args_invalid_queries]">104</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows(s, "a") pattern a(_, _1_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.349000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Number as argument for LHS [assignment_pattern_args_invalid_queries]">105</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows(s, "a") pattern a(1, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.407000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="Invalid expression for assign pattern [assign_pattern_expr_invalid]">106</id><querystr><![CDATA[assign a, a1; variable v; Select BOOLEAN pattern a(v, _"a x b"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.060000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="Invalid expression for assign pattern [assign_pattern_expr_invalid]">107</id><querystr><![CDATA[assign a, a1; variable v; Select BOOLEAN pattern a(v, _"(a + b) / c )"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.645000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as first arg in Follows [follows_parent_string_argument_queries]">108</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.821000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as second arg in Follows [follows_parent_string_argument_queries]">109</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.337000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as first arg in Follows Star [follows_parent_string_argument_queries]">110</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows*("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.593000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as second arg in Follows Star [follows_parent_string_argument_queries]">111</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows*(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.674000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as first arg in Parent [follows_parent_string_argument_queries]">112</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Parent("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.840000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as second arg in Parent [follows_parent_string_argument_queries]">113</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Parent(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.413000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as first arg in Parent Star [follows_parent_string_argument_queries]">114</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Parent*("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.005000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="String as second arg in Parent Star [follows_parent_string_argument_queries]">115</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Parent*(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.956000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Missing semicolon [missing_items_queries]">116</id><querystr><![CDATA[assign a; stmt s constant c; Select BOOLEAN such that Follows("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.876000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Missing design entity [missing_items_queries]">117</id><querystr><![CDATA[assign a; s; constant c; Select BOOLEAN such that Follows(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.704000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="Missing such that [missing_items_queries]">118</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN Follow*("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.707000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Missing bracket [missing_items_queries]">119</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows*(s, "a") pattern a_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.654000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" SuchThat="1" CondNum="3" RelNum="1" comment="String as first arg for Modifies [modifies_uses_first_arg_num]">120</id><querystr><![CDATA[variable v; stmt s, s1; constant c; Select BOOLEAN such that Modifies("1", v)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.923000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Uses="1" SuchThat="1" CondNum="3" RelNum="1" comment="String as first arg for Uses [modifies_uses_first_arg_num]">121</id><querystr><![CDATA[variable v; stmt s, s1; constant c; Select BOOLEAN such that Uses("1", v)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.834000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Design entity spelling [spelling_errors_queries]">122</id><querystr><![CDATA[assign a; stmt s; const c; Select BOOLEAN such that Follows("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.477000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Select clause name spelling [spelling_errors_queries]">123</id><querystr><![CDATA[assign a; stmt s; constant c; Selet s such that Follows(s, "a") pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.898000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="Such that clause spelling [spelling_errors_queries]">124</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follow*("a", s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.212000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="Pattern clause spelling [spelling_errors_queries]">125</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows*(s, "a") patten a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.349000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Modifies clause [string_not_alphanumeric]">126</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Modifies(s, "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.759000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Modifies clause [string_not_alphanumeric]">127</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Modifies(s, ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.135000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Modifies clause [string_not_alphanumeric]">128</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Modifies(s, ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.173000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Modifies clause [string_not_alphanumeric]">129</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Modifies(s, " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.076000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Modifies clause [string_not_alphanumeric]">130</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Modifies(s, "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.305000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Modifies clause [string_not_alphanumeric]">131</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Modifies(s, "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.119000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Modifies clause [string_not_alphanumeric]">132</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Modifies(s, "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.340000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Uses clause [string_not_alphanumeric]">133</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Uses(s, "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.267000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Uses clause [string_not_alphanumeric]">134</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Uses(s, ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.311000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Uses clause [string_not_alphanumeric]">135</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Uses(s, ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.243000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Uses clause [string_not_alphanumeric]">136</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Uses(s, " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.339000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Uses clause [string_not_alphanumeric]">137</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Uses(s, "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>10.399000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Uses clause [string_not_alphanumeric]">138</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Uses(s, "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.525000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Uses clause [string_not_alphanumeric]">139</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Uses(s, "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.457000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="_ in pattern a clause [string_not_alphanumeric]">140</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern a("_", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.623000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment=", in pattern a clause [string_not_alphanumeric]">141</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern a(",", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.694000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment=". in pattern a clause [string_not_alphanumeric]">142</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern a(".", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.585000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="in pattern a clause [string_not_alphanumeric]">143</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern a(" ", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.587000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="in pattern a clause [string_not_alphanumeric]">144</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern a("", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.393000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="/ in pattern a clause [string_not_alphanumeric]">145</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern a("/", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.549000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="a-b in pattern a clause [string_not_alphanumeric]">146</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern a("a-b", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.177000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="4" Pattern="1" SuchThat="1" CondNum="7" RelNum="0" comment="_ in pattern i clause [string_not_alphanumeric]">147</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern i("_", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.348000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment=", in pattern i clause [string_not_alphanumeric]">148</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern i(",", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.267000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment=". in pattern i clause [string_not_alphanumeric]">149</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern i(".", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.146000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="in pattern i clause [string_not_alphanumeric]">150</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern i(" ", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.307000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="in pattern i clause [string_not_alphanumeric]">151</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern i("", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.262000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="/ in pattern i clause [string_not_alphanumeric]">152</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern i("/", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.603000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="a-b in pattern i clause [string_not_alphanumeric]">153</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern i("a-b", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.503000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="6" RelNum="0" comment="_ in pattern w clause [string_not_alphanumeric]">154</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern w("_", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.465000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment=", in pattern w clause [string_not_alphanumeric]">155</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern w(",", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.409000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment=". in pattern w clause [string_not_alphanumeric]">156</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern w(".", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.460000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="in pattern w clause [string_not_alphanumeric]">157</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern w(" ", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.469000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="in pattern w clause [string_not_alphanumeric]">158</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern w("", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.490000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="/ in pattern w clause [string_not_alphanumeric]">159</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern w("/", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.400000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="5" RelNum="0" comment="a-b in pattern w clause [string_not_alphanumeric]">160</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that pattern w("a-b", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.405000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Calls clause on LHS [string_not_alphanumeric]">161</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("_", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.891000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Calls clause on RHS [string_not_alphanumeric]">162</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("abc", "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.524000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="3" SuchThat="1" CondNum="6" RelNum="1" comment="_ in Calls clause on both sides [string_not_alphanumeric]">163</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("_", "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.570000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls clause on LHS [string_not_alphanumeric]">164</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls(",", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.502000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls clause on RHS [string_not_alphanumeric]">165</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("abc", ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.642000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls clause on both sides [string_not_alphanumeric]">166</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls(",", ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.950000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls clause on LHS [string_not_alphanumeric]">167</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls(".", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.748000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls clause on RHS [string_not_alphanumeric]">168</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("abc", ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.392000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls clause on both sides [string_not_alphanumeric]">169</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls(".", ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.674000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on LHS [string_not_alphanumeric]">170</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls(" ", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.173000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on RHS [string_not_alphanumeric]">171</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("abc", " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.404000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on both sides [string_not_alphanumeric]">172</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls(" ", " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.128000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on LHS [string_not_alphanumeric]">173</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.782000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on RHS [string_not_alphanumeric]">174</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("abc", "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.261000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls clause on both sides [string_not_alphanumeric]">175</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("", "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.523000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls clause on LHS [string_not_alphanumeric]">176</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("/", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.152000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls clause on RHS [string_not_alphanumeric]">177</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("abc", "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.105000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls clause on both sides [string_not_alphanumeric]">178</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("/", "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.339000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls clause on LHS [string_not_alphanumeric]">179</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("a-b", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.320000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls clause on RHS [string_not_alphanumeric]">180</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("abc", "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.370000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Calls="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls clause on both sides [string_not_alphanumeric]">181</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls("a-b", "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.034000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Calls* clause on LHS [string_not_alphanumeric]">182</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("_", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.394000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="2" SuchThat="1" CondNum="5" RelNum="1" comment="_ in Calls* clause on RHS [string_not_alphanumeric]">183</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("abc", "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.095000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="3" SuchThat="1" CondNum="6" RelNum="1" comment="_ in Calls* clause on both sides [string_not_alphanumeric]">184</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("_", "_")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.373000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls* clause on LHS [string_not_alphanumeric]">185</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*(",", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.580000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls* clause on RHS [string_not_alphanumeric]">186</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("abc", ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.470000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=", in Calls* clause on both sides [string_not_alphanumeric]">187</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*(",", ",")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.774000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls* clause on LHS [string_not_alphanumeric]">188</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*(".", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.411000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls* clause on RHS [string_not_alphanumeric]">189</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("abc", ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.098000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment=". in Calls* clause on both sides [string_not_alphanumeric]">190</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*(".", ".")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.282000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on LHS [string_not_alphanumeric]">191</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*(" ", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.845000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on RHS [string_not_alphanumeric]">192</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("abc", " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>6.192000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on both sides [string_not_alphanumeric]">193</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*(" ", " ")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.685000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on LHS [string_not_alphanumeric]">194</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.323000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on RHS [string_not_alphanumeric]">195</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("abc", "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.369000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="in Calls* clause on both sides [string_not_alphanumeric]">196</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("", "")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.272000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls* clause on LHS [string_not_alphanumeric]">197</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("/", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.293000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls* clause on RHS [string_not_alphanumeric]">198</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("abc", "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.434000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="/ in Calls* clause on both sides [string_not_alphanumeric]">199</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("/", "/")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.960000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls* clause on LHS [string_not_alphanumeric]">200</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("a-b", "abc")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.963000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls* clause on RHS [string_not_alphanumeric]">201</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("abc", "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.768000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnBoolean="1" Callsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="a-b in Calls* clause on both sides [string_not_alphanumeric]">202</id><querystr><![CDATA[assign a; if i; while w; variable v; stmt s; procedure p; prog_line prog; Select BOOLEAN such that Calls*("a-b", "a-b")]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.383000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
</queries>
</test_results>
