<?xml-stylesheet type="text/xsl" href="analysis.xsl"?>
<test_results>
<info>
<name>autotester</name><parsing_time_taken>6.323000</parsing_time_taken>
</info>
<queries>
<query>
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Assign design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">1</id><querystr><![CDATA[assign a, a1; stmt s, s1; Select s such that Follows(s, s1) pattern a(a1, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.762000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Constant design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">2</id><querystr><![CDATA[assign a; stmt s, s1; constant c; Select s such that Follows(s, s1) pattern a(c, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.200000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="If design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">3</id><querystr><![CDATA[assign a; stmt s, s1; if i; Select s such that Follows(s, s1) pattern a(i, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.196000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Print design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">4</id><querystr><![CDATA[assign a; stmt s, s1; print p; Select s such that Follows(s, s1) pattern a(p, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.438000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Procedure design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">5</id><querystr><![CDATA[assign a; stmt s, s1; procedure p; Select s such that Follows(s, s1) pattern a(p, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.297000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Read design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">6</id><querystr><![CDATA[assign a; stmt s, s1; read r; Select s such that Follows(s, s1) pattern a(r, _"1"_)]]></querystr>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Stmt design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">7</id><querystr><![CDATA[assign a; stmt s, s1; Select s such that Follows(s, s1) pattern a(s, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.227000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="While design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">8</id><querystr><![CDATA[assign a; stmt s, s1; while w; Select s such that Follows(s, s1) pattern a(w, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.240000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Prog line design entity as LHS in Assign Pattern [assignment_pattern_lhs_not_var_queries]">9</id><querystr><![CDATA[prog_line prog; stmt s, s1; assign a; Select s such that Follows(s, s1) pattern a(prog, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.138000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Undeclared design entity as clause argument in such that clause [design_entity_declaration_error_queries]">10</id><querystr><![CDATA[assign a; variable v; Select a such that Modifies(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.992000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Undeclared design entity as clause argument in pattern clause [design_entity_declaration_error_queries]">11</id><querystr><![CDATA[stmt s; variable v; Select s such that Modifies(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.254000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Repeated declaration of same design entity synonym, with different design entity [design_entity_declaration_error_queries]">12</id><querystr><![CDATA[assign a; stmt a; variable v; Select a such that Modifies(a, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.988000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Repeated declaration of same design entity synonym, with same design entity [design_entity_declaration_error_queries]">13</id><querystr><![CDATA[assign a; stmt s, s; variable v; Select s such that Modifies(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.297000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Follows [follows_parent_args_not_stmt_queries]">14</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.073000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Follows [follows_parent_args_not_stmt_queries]">15</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.968000</time_taken>
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
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Follows Star [follows_parent_args_not_stmt_queries]">16</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows*(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.676000</time_taken>
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
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Follows Star [follows_parent_args_not_stmt_queries]">17</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Follows*(s, c) pattern a(_, _"1"_)]]></querystr>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Parent [follows_parent_args_not_stmt_queries]">18</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Parent(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.456000</time_taken>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Parent [follows_parent_args_not_stmt_queries]">19</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Parent(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.860000</time_taken>
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
<id ReturnTuple="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Parent Star [follows_parent_args_not_stmt_queries]">20</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Parent*(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.306000</time_taken>
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
<id ReturnTuple="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Parent Star [follows_parent_args_not_stmt_queries]">21</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Parent*(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.436000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as first arg in Follows [follows_parent_args_not_stmt_queries]">22</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Follows(p, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.706000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Follows [follows_parent_args_not_stmt_queries]">23</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Follows(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.545000</time_taken>
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
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as first arg in Follows Star [follows_parent_args_not_stmt_queries]">24</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Follows*(p, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.408000</time_taken>
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
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Follows Star [follows_parent_args_not_stmt_queries]">25</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Follows*(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.435000</time_taken>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as first arg in Parent [follows_parent_args_not_stmt_queries]">26</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Parent(p, s) pattern a(_, _"1"_)]]></querystr>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Parent [follows_parent_args_not_stmt_queries]">27</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Parent(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.117000</time_taken>
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
<id ReturnTuple="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as first arg in Parent Star [follows_parent_args_not_stmt_queries]">28</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Parent*(p, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.133000</time_taken>
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
<id ReturnTuple="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Parent Star [follows_parent_args_not_stmt_queries]">29</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Parent*(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.042000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Follows [follows_parent_args_not_stmt_queries]">30</id><querystr><![CDATA[assign a; stmt s; variable p; Select s such that Follows(v, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.124000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as second arg in Follows [follows_parent_args_not_stmt_queries]">31</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Follows(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.134000</time_taken>
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
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Follows Star [follows_parent_args_not_stmt_queries]">32</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Follows*(v, s) pattern a(_, _"1"_)]]></querystr>
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
<id ReturnTuple="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as second arg in Follows Star [follows_parent_args_not_stmt_queries]">33</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Follows*(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.017000</time_taken>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Parent [follows_parent_args_not_stmt_queries]">34</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Parent(v, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.924000</time_taken>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as second arg in Parent [follows_parent_args_not_stmt_queries]">35</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Parent(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.240000</time_taken>
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
<id ReturnTuple="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Parent Star [follows_parent_args_not_stmt_queries]">36</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Parent*(v, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.927000</time_taken>
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
<id ReturnTuple="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as second arg in Parent Star [follows_parent_args_not_stmt_queries]">37</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Parent*(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.061000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Assign design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">38</id><querystr><![CDATA[if i; assign a1; stmt s, s1; Select s such that Follows(s, s1) pattern i(a1, _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.039000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">39</id><querystr><![CDATA[if i; stmt s, s1; constant c; Select s such that Follows(s, s1) pattern i(c, _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.158000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="If design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">40</id><querystr><![CDATA[if i; stmt s, s1; if i; Select s such that Follows(s, s1) pattern i(i, _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.117000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Print design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">41</id><querystr><![CDATA[if i; stmt s, s1; print p; Select s such that Follows(s, s1) pattern i(p, _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.962000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">42</id><querystr><![CDATA[if i; stmt s, s1; procedure p; Select s such that Follows(s, s1) pattern i(p, _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.548000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Read design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">43</id><querystr><![CDATA[if i; stmt s, s1; read r; Select s such that Follows(s, s1) pattern i(r, _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.352000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Stmt design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">44</id><querystr><![CDATA[if i; stmt s, s1; Select s such that Follows(s, s1) pattern i(s, _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.378000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="If design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">45</id><querystr><![CDATA[if i; stmt s, s1; if i; Select s such that Follows(s, s1) pattern i(w, _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.377000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="Prog line design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">46</id><querystr><![CDATA[prog_line prog; stmt s, s1; if i; Select s such that Follows(s, s1) pattern i(prog, _, _)]]></querystr>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent clause [integers_with_leading_0s]">47</id><querystr><![CDATA[prog_line p; Select p such that Parent(p, 00100)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>5.691000</time_taken>
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
<id ReturnTuple="1" Parentstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent* clause [integers_with_leading_0s]">48</id><querystr><![CDATA[prog_line p; Select p such that Parent*(p, 00100)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.357000</time_taken>
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
<id ReturnTuple="1" Next="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next clause [integers_with_leading_0s]">49</id><querystr><![CDATA[prog_line p; Select p such that Next(p, 00100)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.414000</time_taken>
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
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next* clause [integers_with_leading_0s]">50</id><querystr><![CDATA[prog_line p; Select p such that Next*(p, 00100)]]></querystr>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows clause [integers_with_leading_0s]">51</id><querystr><![CDATA[prog_line p; Select p such that Follows(p, 00100)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.972000</time_taken>
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
<id ReturnTuple="1" Followsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows* clause [integers_with_leading_0s]">52</id><querystr><![CDATA[prog_line p; Select p such that Follows*(p, 00100)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.199000</time_taken>
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
<id ReturnTuple="1" Affects="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects clause [integers_with_leading_0s]">53</id><querystr><![CDATA[prog_line p; Select p such that Affects(p, 00100)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.205000</time_taken>
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
<id ReturnTuple="1" Affectsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects* clause [integers_with_leading_0s]">54</id><querystr><![CDATA[prog_line p; Select p such that Affects*(p, 00100)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>5.506000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="1" With="1" CondNum="3" RelNum="0" comment="Leading 0s in with clause [integers_with_leading_0s]">55</id><querystr><![CDATA[prog_line p; Select p with p = 00100]]></querystr>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent clause [integers_with_leading_0s]">56</id><querystr><![CDATA[prog_line p; Select p such that Parent(00200, p)]]></querystr>
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
<id ReturnTuple="1" Parentstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent* clause [integers_with_leading_0s]">57</id><querystr><![CDATA[prog_line p; Select p such that Parent*(00200, p)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.949000</time_taken>
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
<id ReturnTuple="1" Next="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next clause [integers_with_leading_0s]">58</id><querystr><![CDATA[prog_line p; Select p such that Next(00200, p)]]></querystr>
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
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next* clause [integers_with_leading_0s]">59</id><querystr><![CDATA[prog_line p; Select p such that Next*(00200, p)]]></querystr>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows clause [integers_with_leading_0s]">60</id><querystr><![CDATA[prog_line p; Select p such that Follows(00200, p)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.902000</time_taken>
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
<id ReturnTuple="1" Followsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows* clause [integers_with_leading_0s]">61</id><querystr><![CDATA[prog_line p; Select p such that Follows*(00200, p)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.946000</time_taken>
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
<id ReturnTuple="1" Modifies="1" SuchThat="1" CondNum="3" RelNum="1" comment="Leading 0s in Modifies clause [integers_with_leading_0s]">62</id><querystr><![CDATA[variable v; Select v such that Modifies(00200, v)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.073000</time_taken>
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
<id ReturnTuple="1" Uses="1" SuchThat="1" CondNum="3" RelNum="1" comment="Leading 0s in Uses clause [integers_with_leading_0s]">63</id><querystr><![CDATA[variable v; Select v such that Uses(00200, v)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.075000</time_taken>
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
<id ReturnTuple="1" Affects="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects clause [integers_with_leading_0s]">64</id><querystr><![CDATA[prog_line p; Select p such that Affects(00200, p)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.176000</time_taken>
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
<id ReturnTuple="1" Affectsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects* clause [integers_with_leading_0s]">65</id><querystr><![CDATA[prog_line p; Select p such that Affects*(00200, p)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.962000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="1" With="1" CondNum="3" RelNum="0" comment="Leading 0s in with clause [integers_with_leading_0s]">66</id><querystr><![CDATA[prog_line p; Select p with 00200 = p]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.959000</time_taken>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent clause [integers_with_leading_0s]">67</id><querystr><![CDATA[prog_line p; Select p such that Parent(00100, 00200)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.328000</time_taken>
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
<id ReturnTuple="1" Parentstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent* clause [integers_with_leading_0s]">68</id><querystr><![CDATA[prog_line p; Select p such that Parent*(00100, 00200)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.589000</time_taken>
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
<id ReturnTuple="1" Next="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next clause [integers_with_leading_0s]">69</id><querystr><![CDATA[prog_line p; Select p such that Next(00100, 00200)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.412000</time_taken>
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
<id ReturnTuple="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next* clause [integers_with_leading_0s]">70</id><querystr><![CDATA[prog_line p; Select p such that Next*(00100, 00200)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.432000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows clause [integers_with_leading_0s]">71</id><querystr><![CDATA[prog_line p; Select p such that Follows(00100, 00200)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.500000</time_taken>
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
<id ReturnTuple="1" Followsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows* clause [integers_with_leading_0s]">72</id><querystr><![CDATA[prog_line p; Select p such that Follows*(00100, 00200)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.683000</time_taken>
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
<id ReturnTuple="1" Affects="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects clause [integers_with_leading_0s]">73</id><querystr><![CDATA[prog_line p; Select p such that Affects(00100, 00200)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.517000</time_taken>
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
<id ReturnTuple="1" Affectsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects* clause [integers_with_leading_0s]">74</id><querystr><![CDATA[prog_line p; Select p such that Affects*(00100, 00200)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>5.742000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="1" With="1" CondNum="3" RelNum="0" comment="Leading 0s in with clause [integers_with_leading_0s]">75</id><querystr><![CDATA[prog_line p; Select p with 00100 = 00200]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.376000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Modifies [modifies_uses_first_arg_variable_constant_queries]">76</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Modifies(v, a) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.857000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Uses [modifies_uses_first_arg_variable_constant_queries]">77</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Uses(v, a) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.151000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Modifies [modifies_uses_first_arg_variable_constant_queries]">78</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Modifies(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.792000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Uses [modifies_uses_first_arg_variable_constant_queries]">79</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Uses(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.083000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="Wildcard as first argument in Modifies [modifies_uses_first_arg_wildcard_queries]">80</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Modifies(_, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.100000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="3" Uses="1" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="Wildcard as first argument in Uses [modifies_uses_first_arg_wildcard_queries]">81</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Uses(_, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.200000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Assign design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">82</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Modifies(s, a) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.059000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Assign design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">83</id><querystr><![CDATA[assign a; stmt s; variable v; Select s such that Uses(s, a) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.161000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">84</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Modifies(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.276000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">85</id><querystr><![CDATA[assign a; stmt s; constant c; Select s such that Uses(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.966000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="If design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">86</id><querystr><![CDATA[assign a; stmt s; if i; Select s such that Modifies(s, i) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.150000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="If design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">87</id><querystr><![CDATA[assign a; stmt s; if i; Select s such that Uses(s, i) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.029000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Print design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">88</id><querystr><![CDATA[assign a; stmt s; print p; Select s such that Modifies(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.148000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Print design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">89</id><querystr><![CDATA[assign a; stmt s; print p; Select s such that Uses(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.144000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">90</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Modifies(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.026000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">91</id><querystr><![CDATA[assign a; stmt s; procedure p; Select s such that Uses(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.909000</time_taken>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Read design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">92</id><querystr><![CDATA[assign a; stmt s; read r; Select s such that Modifies(s, r) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.058000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Read design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">93</id><querystr><![CDATA[assign a; stmt s; read r; Select s such that Uses(s, r) pattern a(_, _"1"_)]]></querystr>
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
<id ReturnTuple="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Stmt design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">94</id><querystr><![CDATA[assign a; stmt s, s1; Select s such that Modifies(s, s1) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.170000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Stmt design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">95</id><querystr><![CDATA[assign a; stmt s, s1; Select s such that Uses(s, s1) pattern a(_, _"1"_)]]></querystr>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Constant design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">96</id><querystr><![CDATA[variable v; stmt s, s1; constant c; Select s such that Follows(s, s1) pattern c(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.510000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Print design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">97</id><querystr><![CDATA[variable v; stmt s, s1; print p; Select s such that Follows(s, s1) pattern p(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.354000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Procedure design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">98</id><querystr><![CDATA[variable v; stmt s, s1; procedure p; Select s such that Follows(s, s1) pattern p(v, _"1"_)]]></querystr>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Read design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">99</id><querystr><![CDATA[variable v; stmt s, s1; read r; Select s such that Follows(s, s1) pattern r(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.333000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Stmt design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">100</id><querystr><![CDATA[variable v; stmt s, s1; Select s such that Follows(s, s1) pattern s1(v, _"1"_)]]></querystr>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Variable design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">101</id><querystr><![CDATA[variable v; stmt s, s1; while w; Select s such that Follows(s, s1) pattern v(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.730000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="While Pattern with 3 args [pattern_wrong_number_of_args]">102</id><querystr><![CDATA[while w; stmt s; Select s pattern w("x", _, _)]]></querystr>
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
<id ReturnTuple="1" UnnamedVar="1" Pattern="1" CondNum="3" RelNum="0" comment="If Pattern with 2 args [pattern_wrong_number_of_args]">103</id><querystr><![CDATA[if i; stmt s; Select s pattern i("x", _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.220000</time_taken>
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
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="Assign Pattern with 3 args [pattern_wrong_number_of_args]">104</id><querystr><![CDATA[assign a; stmt s; Select s pattern a("x", _, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.086000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Assign design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">105</id><querystr><![CDATA[while w; assign a1; stmt s, s1; Select s such that Follows(s, s1) pattern w(a1, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.187000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Constant design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">106</id><querystr><![CDATA[while w; stmt s, s1; constant c; Select s such that Follows(s, s1) pattern w(c, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.619000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="If design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">107</id><querystr><![CDATA[while w; stmt s, s1; if i; Select s such that Follows(s, s1) pattern w(i, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.251000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Print design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">108</id><querystr><![CDATA[while w; stmt s, s1; print p; Select s such that Follows(s, s1) pattern w(p, _)]]></querystr>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Procedure design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">109</id><querystr><![CDATA[while w; stmt s, s1; procedure p; Select s such that Follows(s, s1) pattern w(p, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.949000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Read design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">110</id><querystr><![CDATA[while w; stmt s, s1; read r; Select s such that Follows(s, s1) pattern w(r, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.884000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Stmt design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">111</id><querystr><![CDATA[while w; stmt s, s1; Select s such that Follows(s, s1) pattern w(s, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.985000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="While design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">112</id><querystr><![CDATA[while w; stmt s, s1; while w; Select s such that Follows(s, s1) pattern w(w, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.833000</time_taken>
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
<id ReturnTuple="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Prog line design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">113</id><querystr><![CDATA[prog_line prog; stmt s, s1; while w; Select s such that Follows(s, s1) pattern w(prog, _)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.911000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName const.value [with_clause_invalid_types]">114</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with p.procName = const.value]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.966000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName s1.stmt# [with_clause_invalid_types]">115</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with p.procName = s1.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.870000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName pr.stmt# [with_clause_invalid_types]">116</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with p.procName = pr.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.185000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName c.stmt# [with_clause_invalid_types]">117</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with p.procName = c.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.990000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName r.stmt# [with_clause_invalid_types]">118</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with p.procName = r.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.085000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName w.stmt# [with_clause_invalid_types]">119</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with p.procName = w.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.298000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName ifs.stmt# [with_clause_invalid_types]">120</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with p.procName = ifs.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.224000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName a.stmt# [with_clause_invalid_types]">121</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with p.procName = a.stmt#]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName 100 [with_clause_invalid_types]">122</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with p.procName = 100]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.286000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName const.value [with_clause_invalid_types]">123</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.procName = const.value]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.553000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName s1.stmt# [with_clause_invalid_types]">124</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.procName = s1.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.359000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName pr.stmt# [with_clause_invalid_types]">125</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.procName = pr.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.467000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName c.stmt# [with_clause_invalid_types]">126</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.procName = c.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.252000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName r.stmt# [with_clause_invalid_types]">127</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.procName = r.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.578000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName w.stmt# [with_clause_invalid_types]">128</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.procName = w.stmt#]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName ifs.stmt# [with_clause_invalid_types]">129</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.procName = ifs.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>5.064000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName a.stmt# [with_clause_invalid_types]">130</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.procName = a.stmt#]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName 100 [with_clause_invalid_types]">131</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.procName = 100]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.072000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName const.value [with_clause_invalid_types]">132</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with v.varName = const.value]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.195000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName s1.stmt# [with_clause_invalid_types]">133</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with v.varName = s1.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.935000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName pr.stmt# [with_clause_invalid_types]">134</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with v.varName = pr.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.039000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName c.stmt# [with_clause_invalid_types]">135</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with v.varName = c.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.056000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName r.stmt# [with_clause_invalid_types]">136</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with v.varName = r.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.925000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName w.stmt# [with_clause_invalid_types]">137</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with v.varName = w.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.172000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName ifs.stmt# [with_clause_invalid_types]">138</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with v.varName = ifs.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.092000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName a.stmt# [with_clause_invalid_types]">139</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with v.varName = a.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.942000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName 100 [with_clause_invalid_types]">140</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with v.varName = 100]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.040000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName const.value [with_clause_invalid_types]">141</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.varName = const.value]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.009000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName s1.stmt# [with_clause_invalid_types]">142</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.varName = s1.stmt#]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName pr.stmt# [with_clause_invalid_types]">143</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.varName = pr.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.962000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName c.stmt# [with_clause_invalid_types]">144</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.varName = c.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.923000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName r.stmt# [with_clause_invalid_types]">145</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.varName = r.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.141000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName w.stmt# [with_clause_invalid_types]">146</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.varName = w.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.022000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName ifs.stmt# [with_clause_invalid_types]">147</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.varName = ifs.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.310000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName a.stmt# [with_clause_invalid_types]">148</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.varName = a.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.357000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName 100 [with_clause_invalid_types]">149</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.varName = 100]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName const.value [with_clause_invalid_types]">150</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.varName = const.value]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName s1.stmt# [with_clause_invalid_types]">151</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.varName = s1.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.316000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName pr.stmt# [with_clause_invalid_types]">152</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.varName = pr.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.479000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName c.stmt# [with_clause_invalid_types]">153</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.varName = c.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.398000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName r.stmt# [with_clause_invalid_types]">154</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.varName = r.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.507000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName w.stmt# [with_clause_invalid_types]">155</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.varName = w.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.453000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName ifs.stmt# [with_clause_invalid_types]">156</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.varName = ifs.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.923000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName a.stmt# [with_clause_invalid_types]">157</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.varName = a.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.161000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName 100 [with_clause_invalid_types]">158</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.varName = 100]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.073000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc const.value [with_clause_invalid_types]">159</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with "abc" = const.value]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.913000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc s1.stmt# [with_clause_invalid_types]">160</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with "abc" = s1.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.851000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc pr.stmt# [with_clause_invalid_types]">161</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with "abc" = pr.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.014000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc c.stmt# [with_clause_invalid_types]">162</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with "abc" = c.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.174000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc r.stmt# [with_clause_invalid_types]">163</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with "abc" = r.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.012000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc w.stmt# [with_clause_invalid_types]">164</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with "abc" = w.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.223000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc ifs.stmt# [with_clause_invalid_types]">165</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with "abc" = ifs.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.116000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc a.stmt# [with_clause_invalid_types]">166</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with "abc" = a.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.937000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc 100 [with_clause_invalid_types]">167</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with "abc" = 100]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.058000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value p.procName [with_clause_invalid_types]">168</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with const.value = p.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.878000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value c.procName [with_clause_invalid_types]">169</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with const.value = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.947000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value v.varName [with_clause_invalid_types]">170</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with const.value = v.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.967000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value r.varName [with_clause_invalid_types]">171</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with const.value = r.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.171000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value pr.varName [with_clause_invalid_types]">172</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with const.value = pr.varName]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value abc [with_clause_invalid_types]">173</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with const.value = "abc"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.902000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# p.procName [with_clause_invalid_types]">174</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with s1.stmt# = p.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.494000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# c.procName [with_clause_invalid_types]">175</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with s1.stmt# = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.651000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# v.varName [with_clause_invalid_types]">176</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with s1.stmt# = v.varName]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# r.varName [with_clause_invalid_types]">177</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with s1.stmt# = r.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.412000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# pr.varName [with_clause_invalid_types]">178</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with s1.stmt# = pr.varName]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# abc [with_clause_invalid_types]">179</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with s1.stmt# = "abc"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.538000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# p.procName [with_clause_invalid_types]">180</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.stmt# = p.procName]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# c.procName [with_clause_invalid_types]">181</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.stmt# = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.513000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# v.varName [with_clause_invalid_types]">182</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.stmt# = v.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.032000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# r.varName [with_clause_invalid_types]">183</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.stmt# = r.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.964000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# pr.varName [with_clause_invalid_types]">184</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.stmt# = pr.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.993000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# abc [with_clause_invalid_types]">185</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with pr.stmt# = "abc"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.356000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# p.procName [with_clause_invalid_types]">186</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.stmt# = p.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.995000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# c.procName [with_clause_invalid_types]">187</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.stmt# = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.826000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# v.varName [with_clause_invalid_types]">188</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.stmt# = v.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.554000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# r.varName [with_clause_invalid_types]">189</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.stmt# = r.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.892000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# pr.varName [with_clause_invalid_types]">190</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.stmt# = pr.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.149000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# abc [with_clause_invalid_types]">191</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with c.stmt# = "abc"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.130000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# p.procName [with_clause_invalid_types]">192</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.stmt# = p.procName]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# c.procName [with_clause_invalid_types]">193</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.stmt# = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.090000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# v.varName [with_clause_invalid_types]">194</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.stmt# = v.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.968000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# r.varName [with_clause_invalid_types]">195</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.stmt# = r.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.929000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# pr.varName [with_clause_invalid_types]">196</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.stmt# = pr.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.086000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# abc [with_clause_invalid_types]">197</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with r.stmt# = "abc"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.125000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# p.procName [with_clause_invalid_types]">198</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with w.stmt# = p.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.126000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# c.procName [with_clause_invalid_types]">199</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with w.stmt# = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.529000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# v.varName [with_clause_invalid_types]">200</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with w.stmt# = v.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.365000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# r.varName [with_clause_invalid_types]">201</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with w.stmt# = r.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.230000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# pr.varName [with_clause_invalid_types]">202</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with w.stmt# = pr.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.382000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# abc [with_clause_invalid_types]">203</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with w.stmt# = "abc"]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# p.procName [with_clause_invalid_types]">204</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with ifs.stmt# = p.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.219000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# c.procName [with_clause_invalid_types]">205</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with ifs.stmt# = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.376000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# v.varName [with_clause_invalid_types]">206</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with ifs.stmt# = v.varName]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# r.varName [with_clause_invalid_types]">207</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with ifs.stmt# = r.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.036000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# pr.varName [with_clause_invalid_types]">208</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with ifs.stmt# = pr.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.084000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# abc [with_clause_invalid_types]">209</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with ifs.stmt# = "abc"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.288000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# p.procName [with_clause_invalid_types]">210</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with a.stmt# = p.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.982000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# c.procName [with_clause_invalid_types]">211</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with a.stmt# = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.008000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# v.varName [with_clause_invalid_types]">212</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with a.stmt# = v.varName]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# r.varName [with_clause_invalid_types]">213</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with a.stmt# = r.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.024000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# pr.varName [with_clause_invalid_types]">214</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with a.stmt# = pr.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.091000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# abc [with_clause_invalid_types]">215</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with a.stmt# = "abc"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.148000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 p.procName [with_clause_invalid_types]">216</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with 100 = p.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.317000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 c.procName [with_clause_invalid_types]">217</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with 100 = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.976000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 v.varName [with_clause_invalid_types]">218</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with 100 = v.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.104000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 r.varName [with_clause_invalid_types]">219</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with 100 = r.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.100000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 pr.varName [with_clause_invalid_types]">220</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with 100 = pr.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.156000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 abc [with_clause_invalid_types]">221</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select s with 100 = "abc"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.225000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Procedure entity with varName attribute [with_invalid_attributes_queries]">222</id><querystr><![CDATA[procedure p; Select p with p.varName = "v"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.101000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Procedure entity with value attribute [with_invalid_attributes_queries]">223</id><querystr><![CDATA[procedure p; Select p with p.value = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.112000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Procedure entity with stmt# attribute [with_invalid_attributes_queries]">224</id><querystr><![CDATA[procedure p; Select p with p.stmt# = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.255000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Call entity with varName attribute [with_invalid_attributes_queries]">225</id><querystr><![CDATA[call c; Select c with c.varName = "v"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.389000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Call entity with value attribute [with_invalid_attributes_queries]">226</id><querystr><![CDATA[call c; Select c with c.value = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.252000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Variable entity with procName attribute [with_invalid_attributes_queries]">227</id><querystr><![CDATA[variable v; Select v with v.procName = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.559000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Variable entity with value attribute [with_invalid_attributes_queries]">228</id><querystr><![CDATA[variable v; Select v with v.value = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.461000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Variable entity with stmt# attribute [with_invalid_attributes_queries]">229</id><querystr><![CDATA[variable v; Select v with v.stmt# = "v"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.535000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Read entity with procName attribute [with_invalid_attributes_queries]">230</id><querystr><![CDATA[read r; Select r with r.procName = "p"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.443000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Read entity with value attribute [with_invalid_attributes_queries]">231</id><querystr><![CDATA[read r; Select r with r.value = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.607000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Print entity with procName attribute [with_invalid_attributes_queries]">232</id><querystr><![CDATA[print pr; Select pr with pr.procName = "p"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.644000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Print entity with value attribute [with_invalid_attributes_queries]">233</id><querystr><![CDATA[print pr; Select pr with pr.value = 1]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Constant entity with procName attribute [with_invalid_attributes_queries]">234</id><querystr><![CDATA[constant const; Select const with const.procName = "p"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.070000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Constant entity with varName attribute [with_invalid_attributes_queries]">235</id><querystr><![CDATA[constant const; Select const with const.varName = "v"]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Constant entity with stmt# attribute [with_invalid_attributes_queries]">236</id><querystr><![CDATA[constant const; Select const with const.stmt# = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.355000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Stmt entity with procName attribute [with_invalid_attributes_queries]">237</id><querystr><![CDATA[stmt s; Select const with s.procName = "p"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.474000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Stmt entity with varName attribute [with_invalid_attributes_queries]">238</id><querystr><![CDATA[stmt s; Select const with s.varName = "v"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.225000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Stmt entity with value attribute [with_invalid_attributes_queries]">239</id><querystr><![CDATA[stmt s; Select const with s.value = 1]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="While entity with procName attribute [with_invalid_attributes_queries]">240</id><querystr><![CDATA[while w; Select w with w.procName = "p"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.129000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="While entity with varName attribute [with_invalid_attributes_queries]">241</id><querystr><![CDATA[while w; Select w with w.varName = "v"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>2.920000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="While entity with value attribute [with_invalid_attributes_queries]">242</id><querystr><![CDATA[while w; Select w with w.value = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.061000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="If entity with procName attribute [with_invalid_attributes_queries]">243</id><querystr><![CDATA[if ifs; Select ifs with ifs.procName = "p"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.420000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="If entity with varName attribute [with_invalid_attributes_queries]">244</id><querystr><![CDATA[if ifs; Select ifs with ifs.varName = "v"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.613000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="If entity with value attribute [with_invalid_attributes_queries]">245</id><querystr><![CDATA[if ifs; Select ifs with ifs.value = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.240000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Assign entity with procName attribute [with_invalid_attributes_queries]">246</id><querystr><![CDATA[assign a; Select a with a.procName = "p"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.326000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Assign entity with varName attribute [with_invalid_attributes_queries]">247</id><querystr><![CDATA[assign a; Select a with a.varName = "v"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.578000</time_taken>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="Assign entity with value attribute [with_invalid_attributes_queries]">248</id><querystr><![CDATA[assign a; Select a with a.value = 1]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.186000</time_taken>
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
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Assign design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">249</id><querystr><![CDATA[assign a, a1; stmt s, s1; Select BOOLEAN such that Follows(s, s1) pattern a(a1, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.990000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Constant design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">250</id><querystr><![CDATA[assign a; stmt s, s1; constant c; Select BOOLEAN such that Follows(s, s1) pattern a(c, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.023000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="If design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">251</id><querystr><![CDATA[assign a; stmt s, s1; if i; Select BOOLEAN such that Follows(s, s1) pattern a(i, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.665000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Print design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">252</id><querystr><![CDATA[assign a; stmt s, s1; print p; Select BOOLEAN such that Follows(s, s1) pattern a(p, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.901000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Procedure design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">253</id><querystr><![CDATA[assign a; stmt s, s1; procedure p; Select BOOLEAN such that Follows(s, s1) pattern a(p, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.944000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Read design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">254</id><querystr><![CDATA[assign a; stmt s, s1; read r; Select BOOLEAN such that Follows(s, s1) pattern a(r, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.561000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Stmt design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">255</id><querystr><![CDATA[assign a; stmt s, s1; Select BOOLEAN such that Follows(s, s1) pattern a(s, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.657000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="While design entity as LHS in Assignment Pattern [assignment_pattern_lhs_not_var_queries]">256</id><querystr><![CDATA[assign a; stmt s, s1; while w; Select BOOLEAN such that Follows(s, s1) pattern a(w, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.593000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Prog line design entity as LHS in Assign Pattern [assignment_pattern_lhs_not_var_queries]">257</id><querystr><![CDATA[prog_line prog; stmt s, s1; assign a; Select BOOLEAN such that Follows(s, s1) pattern a(prog, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.854000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Undeclared design entity as clause argument in such that clause [design_entity_declaration_error_queries]">258</id><querystr><![CDATA[assign a; variable v; Select BOOLEAN such that Modifies(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.446000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Undeclared design entity as clause argument in pattern clause [design_entity_declaration_error_queries]">259</id><querystr><![CDATA[stmt s; variable v; Select BOOLEAN such that Modifies(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.795000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Repeated declaration of same design entity synonym, with different design entity [design_entity_declaration_error_queries]">260</id><querystr><![CDATA[assign a; stmt a; variable v; Select BOOLEAN such that Modifies(a, v) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.065000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Repeated declaration of same design entity synonym, with same design entity [design_entity_declaration_error_queries]">261</id><querystr><![CDATA[assign a; stmt s, s; variable v; Select BOOLEAN such that Modifies(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.987000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Follows [follows_parent_args_not_stmt_queries]">262</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.430000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Follows [follows_parent_args_not_stmt_queries]">263</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.918000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Follows Star [follows_parent_args_not_stmt_queries]">264</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows*(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.699000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Follows Star [follows_parent_args_not_stmt_queries]">265</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Follows*(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.561000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Parent [follows_parent_args_not_stmt_queries]">266</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Parent(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.519000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Parent [follows_parent_args_not_stmt_queries]">267</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Parent(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.731000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Parent Star [follows_parent_args_not_stmt_queries]">268</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Parent*(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.841000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Parent Star [follows_parent_args_not_stmt_queries]">269</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Parent*(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.639000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as first arg in Follows [follows_parent_args_not_stmt_queries]">270</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Follows(p, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.503000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Follows [follows_parent_args_not_stmt_queries]">271</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Follows(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.660000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as first arg in Follows Star [follows_parent_args_not_stmt_queries]">272</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Follows*(p, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.791000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Follows Star [follows_parent_args_not_stmt_queries]">273</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Follows*(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.001000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as first arg in Parent [follows_parent_args_not_stmt_queries]">274</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Parent(p, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.387000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Parent [follows_parent_args_not_stmt_queries]">275</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Parent(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.984000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as first arg in Parent Star [follows_parent_args_not_stmt_queries]">276</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Parent*(p, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.136000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Parent Star [follows_parent_args_not_stmt_queries]">277</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Parent*(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.539000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Follows [follows_parent_args_not_stmt_queries]">278</id><querystr><![CDATA[assign a; stmt s; variable p; Select BOOLEAN such that Follows(v, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.577000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as second arg in Follows [follows_parent_args_not_stmt_queries]">279</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Follows(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.523000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Follows Star [follows_parent_args_not_stmt_queries]">280</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Follows*(v, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.396000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as second arg in Follows Star [follows_parent_args_not_stmt_queries]">281</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Follows*(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.385000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Parent [follows_parent_args_not_stmt_queries]">282</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Parent(v, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.435000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as second arg in Parent [follows_parent_args_not_stmt_queries]">283</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Parent(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.037000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Parent Star [follows_parent_args_not_stmt_queries]">284</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Parent*(v, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.596000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as second arg in Parent Star [follows_parent_args_not_stmt_queries]">285</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Parent*(s, v) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.367000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Assign design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">286</id><querystr><![CDATA[if i; assign a1; stmt s, s1; Select BOOLEAN such that Follows(s, s1) pattern i(a1, _, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.171000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">287</id><querystr><![CDATA[if i; stmt s, s1; constant c; Select BOOLEAN such that Follows(s, s1) pattern i(c, _, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.276000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="If design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">288</id><querystr><![CDATA[if i; stmt s, s1; if i; Select BOOLEAN such that Follows(s, s1) pattern i(i, _, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.286000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Print design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">289</id><querystr><![CDATA[if i; stmt s, s1; print p; Select BOOLEAN such that Follows(s, s1) pattern i(p, _, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.270000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">290</id><querystr><![CDATA[if i; stmt s, s1; procedure p; Select BOOLEAN such that Follows(s, s1) pattern i(p, _, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.015000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Read design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">291</id><querystr><![CDATA[if i; stmt s, s1; read r; Select BOOLEAN such that Follows(s, s1) pattern i(r, _, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.118000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Stmt design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">292</id><querystr><![CDATA[if i; stmt s, s1; Select BOOLEAN such that Follows(s, s1) pattern i(s, _, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.368000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="If design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">293</id><querystr><![CDATA[if i; stmt s, s1; if i; Select BOOLEAN such that Follows(s, s1) pattern i(w, _, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.589000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="Prog line design entity as LHS in If Pattern [if_pattern_lhs_not_var_queries]">294</id><querystr><![CDATA[prog_line prog; stmt s, s1; if i; Select BOOLEAN such that Follows(s, s1) pattern i(prog, _, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.379000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent clause [integers_with_leading_0s]">295</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Parent(p, 00100)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.970000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent* clause [integers_with_leading_0s]">296</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Parent*(p, 00100)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.112000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Next="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next clause [integers_with_leading_0s]">297</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Next(p, 00100)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.449000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next* clause [integers_with_leading_0s]">298</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Next*(p, 00100)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.610000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows clause [integers_with_leading_0s]">299</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Follows(p, 00100)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.954000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows* clause [integers_with_leading_0s]">300</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Follows*(p, 00100)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.843000</time_taken>
<passed/>
</query>
<query>
<id Affects="1" ReturnBoolean="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects clause [integers_with_leading_0s]">301</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Affects(p, 00100)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.258000</time_taken>
<passed/>
</query>
<query>
<id Affectsstar="1" ReturnBoolean="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects* clause [integers_with_leading_0s]">302</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Affects*(p, 00100)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.513000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="1" With="1" CondNum="3" RelNum="0" comment="Leading 0s in with clause [integers_with_leading_0s]">303</id><querystr><![CDATA[prog_line p; Select BOOLEAN with p = 00100]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.424000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent clause [integers_with_leading_0s]">304</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Parent(00200, p)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.134000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent* clause [integers_with_leading_0s]">305</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Parent*(00200, p)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.431000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Next="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next clause [integers_with_leading_0s]">306</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Next(00200, p)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.291000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next* clause [integers_with_leading_0s]">307</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Next*(00200, p)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.374000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows clause [integers_with_leading_0s]">308</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Follows(00200, p)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.742000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows* clause [integers_with_leading_0s]">309</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Follows*(00200, p)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.907000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" SuchThat="1" CondNum="3" RelNum="1" comment="Leading 0s in Modifies clause [integers_with_leading_0s]">310</id><querystr><![CDATA[variable v; Select BOOLEAN such that Modifies(00200, v)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.710000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Uses="1" SuchThat="1" CondNum="3" RelNum="1" comment="Leading 0s in Uses clause [integers_with_leading_0s]">311</id><querystr><![CDATA[variable v; Select BOOLEAN such that Uses(00200, v)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.861000</time_taken>
<passed/>
</query>
<query>
<id Affects="1" ReturnBoolean="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects clause [integers_with_leading_0s]">312</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Affects(00200, p)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.207000</time_taken>
<passed/>
</query>
<query>
<id Affectsstar="1" ReturnBoolean="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects* clause [integers_with_leading_0s]">313</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Affects*(00200, p)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.885000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="1" With="1" CondNum="3" RelNum="0" comment="Leading 0s in with clause [integers_with_leading_0s]">314</id><querystr><![CDATA[prog_line p; Select BOOLEAN with 00200 = p]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.219000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parent="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent clause [integers_with_leading_0s]">315</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Parent(00100, 00200)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.390000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Parentstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Parent* clause [integers_with_leading_0s]">316</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Parent*(00100, 00200)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.433000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Next="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next clause [integers_with_leading_0s]">317</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Next(00100, 00200)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.401000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Nextstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Next* clause [integers_with_leading_0s]">318</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Next*(00100, 00200)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.733000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows clause [integers_with_leading_0s]">319</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Follows(00100, 00200)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.409000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Followsstar="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Follows* clause [integers_with_leading_0s]">320</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Follows*(00100, 00200)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.344000</time_taken>
<passed/>
</query>
<query>
<id Affects="1" ReturnBoolean="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects clause [integers_with_leading_0s]">321</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Affects(00100, 00200)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.465000</time_taken>
<passed/>
</query>
<query>
<id Affectsstar="1" ReturnBoolean="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Leading 0s in Affects* clause [integers_with_leading_0s]">322</id><querystr><![CDATA[prog_line p; Select BOOLEAN such that Affects*(00100, 00200)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.606000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="1" With="1" CondNum="3" RelNum="0" comment="Leading 0s in with clause [integers_with_leading_0s]">323</id><querystr><![CDATA[prog_line p; Select BOOLEAN with 00100 = 00200]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.671000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Modifies [modifies_uses_first_arg_variable_constant_queries]">324</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Modifies(v, a) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.533000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Variable design entity as first arg in Uses [modifies_uses_first_arg_variable_constant_queries]">325</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Uses(v, a) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.781000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Modifies [modifies_uses_first_arg_variable_constant_queries]">326</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Modifies(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.552000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as first arg in Uses [modifies_uses_first_arg_variable_constant_queries]">327</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Uses(c, s) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.656000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="Wildcard as first argument in Modifies [modifies_uses_first_arg_wildcard_queries]">328</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Modifies(_, v) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.444000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="3" Uses="1" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="Wildcard as first argument in Uses [modifies_uses_first_arg_wildcard_queries]">329</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Uses(_, v) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.606000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Assign design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">330</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Modifies(s, a) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.242000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Assign design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">331</id><querystr><![CDATA[assign a; stmt s; variable v; Select BOOLEAN such that Uses(s, a) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.137000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">332</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Modifies(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.247000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Constant design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">333</id><querystr><![CDATA[assign a; stmt s; constant c; Select BOOLEAN such that Uses(s, c) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.933000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="If design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">334</id><querystr><![CDATA[assign a; stmt s; if i; Select BOOLEAN such that Modifies(s, i) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.349000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="If design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">335</id><querystr><![CDATA[assign a; stmt s; if i; Select BOOLEAN such that Uses(s, i) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.259000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Print design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">336</id><querystr><![CDATA[assign a; stmt s; print p; Select BOOLEAN such that Modifies(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.260000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Print design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">337</id><querystr><![CDATA[assign a; stmt s; print p; Select BOOLEAN such that Uses(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.293000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">338</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Modifies(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.607000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Procedure design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">339</id><querystr><![CDATA[assign a; stmt s; procedure p; Select BOOLEAN such that Uses(s, p) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.628000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Read design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">340</id><querystr><![CDATA[assign a; stmt s; read r; Select BOOLEAN such that Modifies(s, r) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.778000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Read design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">341</id><querystr><![CDATA[assign a; stmt s; read r; Select BOOLEAN such that Uses(s, r) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.868000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Modifies="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Stmt design entity as second arg in Modifies [modifies_uses_second_arg_stmt_queries]">342</id><querystr><![CDATA[assign a; stmt s, s1; Select BOOLEAN such that Modifies(s, s1) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.865000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" UnnamedVar="2" Uses="1" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Stmt design entity as second arg in Uses [modifies_uses_second_arg_stmt_queries]">343</id><querystr><![CDATA[assign a; stmt s, s1; Select BOOLEAN such that Uses(s, s1) pattern a(_, _"1"_)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.049000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Constant design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">344</id><querystr><![CDATA[variable v; stmt s, s1; constant c; Select BOOLEAN such that Follows(s, s1) pattern c(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.780000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Print design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">345</id><querystr><![CDATA[variable v; stmt s, s1; print p; Select BOOLEAN such that Follows(s, s1) pattern p(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.361000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Procedure design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">346</id><querystr><![CDATA[variable v; stmt s, s1; procedure p; Select BOOLEAN such that Follows(s, s1) pattern p(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.263000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Read design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">347</id><querystr><![CDATA[variable v; stmt s, s1; read r; Select BOOLEAN such that Follows(s, s1) pattern r(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.358000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Stmt design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">348</id><querystr><![CDATA[variable v; stmt s, s1; Select BOOLEAN such that Follows(s, s1) pattern s1(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.015000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Variable design entity as LHS in Pattern [pattern_first_arg_not_valid_entity_queries]">349</id><querystr><![CDATA[variable v; stmt s, s1; while w; Select BOOLEAN such that Follows(s, s1) pattern v(v, _"1"_)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.654000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="While Pattern with 3 args [pattern_wrong_number_of_args]">350</id><querystr><![CDATA[while w; stmt s; Select BOOLEAN pattern w("x", _, _)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.511000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" UnnamedVar="1" Pattern="1" CondNum="3" RelNum="0" comment="If Pattern with 2 args [pattern_wrong_number_of_args]">351</id><querystr><![CDATA[if i; stmt s; Select BOOLEAN pattern i("x", _)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.490000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="Assign Pattern with 3 args [pattern_wrong_number_of_args]">352</id><querystr><![CDATA[assign a; stmt s; Select BOOLEAN pattern a("x", _, _)]]></querystr>
<stuans></stuans>
<correct>FALSE</correct>
<time_taken>3.642000</time_taken>
<failed>
<missing>FALSE</missing>
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
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Assign design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">353</id><querystr><![CDATA[while w; assign a1; stmt s, s1; Select BOOLEAN such that Follows(s, s1) pattern w(a1, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.564000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Constant design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">354</id><querystr><![CDATA[while w; stmt s, s1; constant c; Select BOOLEAN such that Follows(s, s1) pattern w(c, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.648000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="If design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">355</id><querystr><![CDATA[while w; stmt s, s1; if i; Select BOOLEAN such that Follows(s, s1) pattern w(i, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.694000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Print design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">356</id><querystr><![CDATA[while w; stmt s, s1; print p; Select BOOLEAN such that Follows(s, s1) pattern w(p, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.583000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Procedure design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">357</id><querystr><![CDATA[while w; stmt s, s1; procedure p; Select BOOLEAN such that Follows(s, s1) pattern w(p, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.427000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Read design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">358</id><querystr><![CDATA[while w; stmt s, s1; read r; Select BOOLEAN such that Follows(s, s1) pattern w(r, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.458000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="Stmt design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">359</id><querystr><![CDATA[while w; stmt s, s1; Select BOOLEAN such that Follows(s, s1) pattern w(s, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.343000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="While design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">360</id><querystr><![CDATA[while w; stmt s, s1; while w; Select BOOLEAN such that Follows(s, s1) pattern w(w, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.431000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" Follows="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="Prog line design entity as LHS in While Pattern [while_pattern_lhs_not_var_queries]">361</id><querystr><![CDATA[prog_line prog; stmt s, s1; while w; Select BOOLEAN such that Follows(s, s1) pattern w(prog, _)]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.310000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName const.value [with_clause_invalid_types]">362</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with p.procName = const.value]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.193000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName s1.stmt# [with_clause_invalid_types]">363</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with p.procName = s1.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.325000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName pr.stmt# [with_clause_invalid_types]">364</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with p.procName = pr.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.194000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName c.stmt# [with_clause_invalid_types]">365</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with p.procName = c.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.685000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName r.stmt# [with_clause_invalid_types]">366</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with p.procName = r.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.617000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName w.stmt# [with_clause_invalid_types]">367</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with p.procName = w.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.460000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName ifs.stmt# [with_clause_invalid_types]">368</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with p.procName = ifs.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.405000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName a.stmt# [with_clause_invalid_types]">369</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with p.procName = a.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.274000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types p.procName 100 [with_clause_invalid_types]">370</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with p.procName = 100]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.058000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName const.value [with_clause_invalid_types]">371</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.procName = const.value]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.249000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName s1.stmt# [with_clause_invalid_types]">372</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.procName = s1.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.281000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName pr.stmt# [with_clause_invalid_types]">373</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.procName = pr.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.925000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName c.stmt# [with_clause_invalid_types]">374</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.procName = c.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.036000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName r.stmt# [with_clause_invalid_types]">375</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.procName = r.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.858000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName w.stmt# [with_clause_invalid_types]">376</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.procName = w.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.981000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName ifs.stmt# [with_clause_invalid_types]">377</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.procName = ifs.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName a.stmt# [with_clause_invalid_types]">378</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.procName = a.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.027000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types c.procName 100 [with_clause_invalid_types]">379</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.procName = 100]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.938000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName const.value [with_clause_invalid_types]">380</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with v.varName = const.value]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.965000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName s1.stmt# [with_clause_invalid_types]">381</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with v.varName = s1.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.832000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName pr.stmt# [with_clause_invalid_types]">382</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with v.varName = pr.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.914000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName c.stmt# [with_clause_invalid_types]">383</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with v.varName = c.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.135000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName r.stmt# [with_clause_invalid_types]">384</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with v.varName = r.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.012000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName w.stmt# [with_clause_invalid_types]">385</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with v.varName = w.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.097000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName ifs.stmt# [with_clause_invalid_types]">386</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with v.varName = ifs.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.253000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName a.stmt# [with_clause_invalid_types]">387</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with v.varName = a.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.896000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types v.varName 100 [with_clause_invalid_types]">388</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with v.varName = 100]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.208000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName const.value [with_clause_invalid_types]">389</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.varName = const.value]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.008000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName s1.stmt# [with_clause_invalid_types]">390</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.varName = s1.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.979000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName pr.stmt# [with_clause_invalid_types]">391</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.varName = pr.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.060000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName c.stmt# [with_clause_invalid_types]">392</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.varName = c.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.009000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName r.stmt# [with_clause_invalid_types]">393</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.varName = r.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.080000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName w.stmt# [with_clause_invalid_types]">394</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.varName = w.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.129000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName ifs.stmt# [with_clause_invalid_types]">395</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.varName = ifs.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.136000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName a.stmt# [with_clause_invalid_types]">396</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.varName = a.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.378000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types r.varName 100 [with_clause_invalid_types]">397</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.varName = 100]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.994000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName const.value [with_clause_invalid_types]">398</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.varName = const.value]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.232000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName s1.stmt# [with_clause_invalid_types]">399</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.varName = s1.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.023000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName pr.stmt# [with_clause_invalid_types]">400</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.varName = pr.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.023000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName c.stmt# [with_clause_invalid_types]">401</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.varName = c.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.926000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName r.stmt# [with_clause_invalid_types]">402</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.varName = r.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.083000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName w.stmt# [with_clause_invalid_types]">403</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.varName = w.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.014000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName ifs.stmt# [with_clause_invalid_types]">404</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.varName = ifs.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.509000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName a.stmt# [with_clause_invalid_types]">405</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.varName = a.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.213000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types pr.varName 100 [with_clause_invalid_types]">406</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.varName = 100]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.128000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc const.value [with_clause_invalid_types]">407</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with "abc" = const.value]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.077000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc s1.stmt# [with_clause_invalid_types]">408</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with "abc" = s1.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.250000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc pr.stmt# [with_clause_invalid_types]">409</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with "abc" = pr.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.749000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc c.stmt# [with_clause_invalid_types]">410</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with "abc" = c.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.141000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc r.stmt# [with_clause_invalid_types]">411</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with "abc" = r.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.989000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc w.stmt# [with_clause_invalid_types]">412</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with "abc" = w.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.064000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc ifs.stmt# [with_clause_invalid_types]">413</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with "abc" = ifs.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>7.503000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc a.stmt# [with_clause_invalid_types]">414</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with "abc" = a.stmt#]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.945000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with string and int types abc 100 [with_clause_invalid_types]">415</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with "abc" = 100]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.724000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value p.procName [with_clause_invalid_types]">416</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with const.value = p.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.710000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value c.procName [with_clause_invalid_types]">417</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with const.value = c.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.567000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value v.varName [with_clause_invalid_types]">418</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with const.value = v.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.765000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value r.varName [with_clause_invalid_types]">419</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with const.value = r.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.649000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value pr.varName [with_clause_invalid_types]">420</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with const.value = pr.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.519000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types const.value abc [with_clause_invalid_types]">421</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with const.value = "abc"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.795000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# p.procName [with_clause_invalid_types]">422</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with s1.stmt# = p.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.361000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# c.procName [with_clause_invalid_types]">423</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with s1.stmt# = c.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.550000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# v.varName [with_clause_invalid_types]">424</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with s1.stmt# = v.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.522000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# r.varName [with_clause_invalid_types]">425</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with s1.stmt# = r.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.825000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# pr.varName [with_clause_invalid_types]">426</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with s1.stmt# = pr.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.643000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types s1.stmt# abc [with_clause_invalid_types]">427</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with s1.stmt# = "abc"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.479000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# p.procName [with_clause_invalid_types]">428</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.stmt# = p.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.563000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# c.procName [with_clause_invalid_types]">429</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.stmt# = c.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.193000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# v.varName [with_clause_invalid_types]">430</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.stmt# = v.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.764000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# r.varName [with_clause_invalid_types]">431</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.stmt# = r.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.700000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# pr.varName [with_clause_invalid_types]">432</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.stmt# = pr.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.993000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types pr.stmt# abc [with_clause_invalid_types]">433</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with pr.stmt# = "abc"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.518000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# p.procName [with_clause_invalid_types]">434</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.stmt# = p.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.713000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# c.procName [with_clause_invalid_types]">435</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.stmt# = c.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.878000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# v.varName [with_clause_invalid_types]">436</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.stmt# = v.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.789000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# r.varName [with_clause_invalid_types]">437</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.stmt# = r.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.688000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# pr.varName [with_clause_invalid_types]">438</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.stmt# = pr.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.741000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types c.stmt# abc [with_clause_invalid_types]">439</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with c.stmt# = "abc"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.769000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# p.procName [with_clause_invalid_types]">440</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.stmt# = p.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.616000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# c.procName [with_clause_invalid_types]">441</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.stmt# = c.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.383000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# v.varName [with_clause_invalid_types]">442</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.stmt# = v.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.710000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# r.varName [with_clause_invalid_types]">443</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.stmt# = r.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.434000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# pr.varName [with_clause_invalid_types]">444</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.stmt# = pr.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.532000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types r.stmt# abc [with_clause_invalid_types]">445</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with r.stmt# = "abc"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.437000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# p.procName [with_clause_invalid_types]">446</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with w.stmt# = p.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.745000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# c.procName [with_clause_invalid_types]">447</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with w.stmt# = c.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.915000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# v.varName [with_clause_invalid_types]">448</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with w.stmt# = v.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.860000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# r.varName [with_clause_invalid_types]">449</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with w.stmt# = r.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.172000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# pr.varName [with_clause_invalid_types]">450</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with w.stmt# = pr.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.673000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types w.stmt# abc [with_clause_invalid_types]">451</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with w.stmt# = "abc"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.663000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# p.procName [with_clause_invalid_types]">452</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with ifs.stmt# = p.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.976000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# c.procName [with_clause_invalid_types]">453</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with ifs.stmt# = c.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.741000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# v.varName [with_clause_invalid_types]">454</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with ifs.stmt# = v.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.111000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# r.varName [with_clause_invalid_types]">455</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with ifs.stmt# = r.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.987000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# pr.varName [with_clause_invalid_types]">456</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with ifs.stmt# = pr.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.759000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types ifs.stmt# abc [with_clause_invalid_types]">457</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with ifs.stmt# = "abc"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.784000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# p.procName [with_clause_invalid_types]">458</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with a.stmt# = p.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.545000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# c.procName [with_clause_invalid_types]">459</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with a.stmt# = c.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.689000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# v.varName [with_clause_invalid_types]">460</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with a.stmt# = v.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.468000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# r.varName [with_clause_invalid_types]">461</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with a.stmt# = r.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.770000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# pr.varName [with_clause_invalid_types]">462</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with a.stmt# = pr.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.446000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types a.stmt# abc [with_clause_invalid_types]">463</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with a.stmt# = "abc"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.518000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 p.procName [with_clause_invalid_types]">464</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with 100 = p.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.818000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 c.procName [with_clause_invalid_types]">465</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with 100 = c.procName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.593000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 v.varName [with_clause_invalid_types]">466</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with 100 = v.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.473000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 r.varName [with_clause_invalid_types]">467</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with 100 = r.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.391000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 pr.varName [with_clause_invalid_types]">468</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with 100 = pr.varName]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.532000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="with int and string types 100 abc [with_clause_invalid_types]">469</id><querystr><![CDATA[assign a; procedure p; stmt s, s1; call c; variable v; read r; print pr; constant const; while w; if ifs; Select BOOLEAN with 100 = "abc"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.550000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Procedure entity with varName attribute [with_invalid_attributes_queries]">470</id><querystr><![CDATA[procedure p; Select BOOLEAN with p.varName = "v"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.623000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Procedure entity with value attribute [with_invalid_attributes_queries]">471</id><querystr><![CDATA[procedure p; Select BOOLEAN with p.value = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.556000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Procedure entity with stmt# attribute [with_invalid_attributes_queries]">472</id><querystr><![CDATA[procedure p; Select BOOLEAN with p.stmt# = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.871000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Call entity with varName attribute [with_invalid_attributes_queries]">473</id><querystr><![CDATA[call c; Select BOOLEAN with c.varName = "v"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>4.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Call entity with value attribute [with_invalid_attributes_queries]">474</id><querystr><![CDATA[call c; Select BOOLEAN with c.value = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.729000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Variable entity with procName attribute [with_invalid_attributes_queries]">475</id><querystr><![CDATA[variable v; Select BOOLEAN with v.procName = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.692000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Variable entity with value attribute [with_invalid_attributes_queries]">476</id><querystr><![CDATA[variable v; Select BOOLEAN with v.value = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.206000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Variable entity with stmt# attribute [with_invalid_attributes_queries]">477</id><querystr><![CDATA[variable v; Select BOOLEAN with v.stmt# = "v"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.488000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Read entity with procName attribute [with_invalid_attributes_queries]">478</id><querystr><![CDATA[read r; Select BOOLEAN with r.procName = "p"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.595000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Read entity with value attribute [with_invalid_attributes_queries]">479</id><querystr><![CDATA[read r; Select BOOLEAN with r.value = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.524000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Print entity with procName attribute [with_invalid_attributes_queries]">480</id><querystr><![CDATA[print pr; Select BOOLEAN with pr.procName = "p"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.585000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Print entity with value attribute [with_invalid_attributes_queries]">481</id><querystr><![CDATA[print pr; Select BOOLEAN with pr.value = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.229000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Constant entity with procName attribute [with_invalid_attributes_queries]">482</id><querystr><![CDATA[constant const; Select BOOLEAN with const.procName = "p"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.658000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Constant entity with varName attribute [with_invalid_attributes_queries]">483</id><querystr><![CDATA[constant const; Select BOOLEAN with const.varName = "v"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.431000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Constant entity with stmt# attribute [with_invalid_attributes_queries]">484</id><querystr><![CDATA[constant const; Select BOOLEAN with const.stmt# = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.384000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Stmt entity with procName attribute [with_invalid_attributes_queries]">485</id><querystr><![CDATA[stmt s; Select BOOLEAN with s.procName = "p"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.457000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Stmt entity with varName attribute [with_invalid_attributes_queries]">486</id><querystr><![CDATA[stmt s; Select BOOLEAN with s.varName = "v"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.493000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Stmt entity with value attribute [with_invalid_attributes_queries]">487</id><querystr><![CDATA[stmt s; Select BOOLEAN with s.value = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.548000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="While entity with procName attribute [with_invalid_attributes_queries]">488</id><querystr><![CDATA[while w; Select BOOLEAN with w.procName = "p"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.499000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="While entity with varName attribute [with_invalid_attributes_queries]">489</id><querystr><![CDATA[while w; Select BOOLEAN with w.varName = "v"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.501000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="While entity with value attribute [with_invalid_attributes_queries]">490</id><querystr><![CDATA[while w; Select BOOLEAN with w.value = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.341000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="If entity with procName attribute [with_invalid_attributes_queries]">491</id><querystr><![CDATA[if ifs; Select BOOLEAN with ifs.procName = "p"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.008000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="If entity with varName attribute [with_invalid_attributes_queries]">492</id><querystr><![CDATA[if ifs; Select BOOLEAN with ifs.varName = "v"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.048000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="If entity with value attribute [with_invalid_attributes_queries]">493</id><querystr><![CDATA[if ifs; Select BOOLEAN with ifs.value = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.127000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Assign entity with procName attribute [with_invalid_attributes_queries]">494</id><querystr><![CDATA[assign a; Select BOOLEAN with a.procName = "p"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>3.426000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Assign entity with varName attribute [with_invalid_attributes_queries]">495</id><querystr><![CDATA[assign a; Select BOOLEAN with a.varName = "v"]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.771000</time_taken>
<passed/>
</query>
<query>
<id ReturnBoolean="1" With="1" CondNum="2" RelNum="0" comment="Assign entity with value attribute [with_invalid_attributes_queries]">496</id><querystr><![CDATA[assign a; Select BOOLEAN with a.value = 1]]></querystr>
<stuans>FALSE</stuans>
<correct>FALSE</correct>
<time_taken>2.910000</time_taken>
<passed/>
</query>
</queries>
</test_results>
