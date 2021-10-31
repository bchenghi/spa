<?xml-stylesheet type="text/xsl" href="analysis.xsl"?>
<test_results>
<info>
<name>autotester</name><parsing_time_taken>13.893000</parsing_time_taken>
</info>
<queries>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="procedure with given name LHS">1</id><querystr><![CDATA[procedure p; Select p with p.procName = "simple"]]></querystr>
<stuans>simple</stuans>
<correct>simple</correct>
<time_taken>4.315000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="procedure with given name RHS">2</id><querystr><![CDATA[procedure p; Select p with "aprocname" = p.procName]]></querystr>
<stuans>aprocname</stuans>
<correct>aprocname</correct>
<time_taken>3.706000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no proc found for given name">3</id><querystr><![CDATA[procedure p; Select p with "notfound" = p.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.805000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="variable with given name LHS">4</id><querystr><![CDATA[variable v; Select v with v.varName = "aprocname"]]></querystr>
<stuans>aprocname</stuans>
<correct>aprocname</correct>
<time_taken>3.828000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="variable with given name RHS">5</id><querystr><![CDATA[variable v; Select v with "u" = v.varName]]></querystr>
<stuans>u</stuans>
<correct>u</correct>
<time_taken>4.088000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no variable found for given name">6</id><querystr><![CDATA[variable v; Select v with v.varName = "d"]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.719000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="call with given procedure name LHS">7</id><querystr><![CDATA[call c; Select c with c.procName = "aprocname"]]></querystr>
<stuans>5</stuans>
<correct>5</correct>
<time_taken>3.901000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="call with given procedure name RHS">8</id><querystr><![CDATA[call c; Select c with "other" = c.procName]]></querystr>
<stuans>17</stuans>
<correct>17</correct>
<time_taken>3.706000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no call found for given procedure name">9</id><querystr><![CDATA[call c; Select c with "notfound" = c.procName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>4.202000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="call with given stmt# LHS">10</id><querystr><![CDATA[call c; Select c with c.stmt# = 17]]></querystr>
<stuans>17</stuans>
<correct>17</correct>
<time_taken>3.834000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="call with given stmt# RHS">11</id><querystr><![CDATA[call c; Select c with 5 = c.stmt#]]></querystr>
<stuans>5</stuans>
<correct>5</correct>
<time_taken>3.823000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no call found for given stmt#">12</id><querystr><![CDATA[call c; Select c with c.stmt# = 35]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.880000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="read with given variable name LHS">13</id><querystr><![CDATA[read rd; Select rd with rd.varName = "x"]]></querystr>
<stuans>20</stuans>
<correct>20</correct>
<time_taken>3.708000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="read with given variable name RHS">14</id><querystr><![CDATA[read rd; Select rd with "u" = rd.varName]]></querystr>
<stuans>12</stuans>
<correct>12</correct>
<time_taken>3.375000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no read found for given variable name">15</id><querystr><![CDATA[read rd; Select rd with "aprocname" = rd.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.596000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="read with given stmt# LHS">16</id><querystr><![CDATA[read rd; Select rd with rd.stmt# = 7]]></querystr>
<stuans>7</stuans>
<correct>7</correct>
<time_taken>3.405000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="read with given stmt# RHS">17</id><querystr><![CDATA[read rd; Select rd with 12 = rd.stmt#]]></querystr>
<stuans>12</stuans>
<correct>12</correct>
<time_taken>3.412000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no read found for given stmt#">18</id><querystr><![CDATA[read rd; Select rd with rd.stmt# = 8]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="print with given variable name LHS">19</id><querystr><![CDATA[print pt; Select pt with pt.varName = "x"]]></querystr>
<stuans>6</stuans>
<correct>6</correct>
<time_taken>3.285000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="print with given variable name RHS">20</id><querystr><![CDATA[print pt; Select pt with "u" = pt.varName]]></querystr>
<stuans>16,19</stuans>
<correct>16,19</correct>
<time_taken>4.636000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no print found for given variable name">21</id><querystr><![CDATA[print pt; Select pt with "count" = pt.varName]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.325000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="print with given stmt# LHS">22</id><querystr><![CDATA[print pt; Select pt with pt.stmt# = 6]]></querystr>
<stuans>6</stuans>
<correct>6</correct>
<time_taken>3.606000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="print with given stmt# LHS">23</id><querystr><![CDATA[print pt; Select pt with 16 = pt.stmt#]]></querystr>
<stuans>16</stuans>
<correct>16</correct>
<time_taken>3.387000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no print found for given stmt#">24</id><querystr><![CDATA[print pt; Select pt with pt.stmt# = 7]]></querystr>
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
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="constant with given value LHS">25</id><querystr><![CDATA[constant const; Select const with const.value = 100]]></querystr>
<stuans>100</stuans>
<correct>100</correct>
<time_taken>3.291000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="constant with given value LHS">26</id><querystr><![CDATA[constant const; Select const with 3 = const.value]]></querystr>
<stuans>3</stuans>
<correct>3</correct>
<time_taken>3.205000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no constant found for given value">27</id><querystr><![CDATA[constant const; Select const with const.value = 100100]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.447000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="stmt with given stmt# LHS">28</id><querystr><![CDATA[stmt s; Select s with s.stmt# = 10]]></querystr>
<stuans>10</stuans>
<correct>10</correct>
<time_taken>3.278000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="stmt with given stmt# RHS">29</id><querystr><![CDATA[stmt s; Select s with 22 = s.stmt#]]></querystr>
<stuans>22</stuans>
<correct>22</correct>
<time_taken>3.454000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no stmt found for given stmt#">30</id><querystr><![CDATA[stmt s; Select s with 27 = s.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.620000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="while with given stmt# LHS">31</id><querystr><![CDATA[while w; Select w with w.stmt# = 14]]></querystr>
<stuans>14</stuans>
<correct>14</correct>
<time_taken>3.425000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="while with given stmt# RHS">32</id><querystr><![CDATA[while w; Select w with 23 = w.stmt#]]></querystr>
<stuans>23</stuans>
<correct>23</correct>
<time_taken>3.499000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no while found for given stmt#">33</id><querystr><![CDATA[while w; Select w with 15 = w.stmt#]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.938000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="if with given stmt# LHS">34</id><querystr><![CDATA[if i; Select i with i.stmt# = 8]]></querystr>
<stuans>8</stuans>
<correct>8</correct>
<time_taken>3.228000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="if with given stmt# RHS">35</id><querystr><![CDATA[if i; Select i with 24 = i.stmt#]]></querystr>
<stuans>24</stuans>
<correct>24</correct>
<time_taken>3.581000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no if found for given stmt#">36</id><querystr><![CDATA[if i; Select i with i.stmt# = 10]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.733000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="assign with given stmt# LHS">37</id><querystr><![CDATA[assign a; Select a with a.stmt# = 1]]></querystr>
<stuans>1</stuans>
<correct>1</correct>
<time_taken>3.845000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="assign with given stmt# RHS">38</id><querystr><![CDATA[assign a; Select a with 18 = a.stmt#]]></querystr>
<stuans>18</stuans>
<correct>18</correct>
<time_taken>3.945000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" With="1" CondNum="2" RelNum="0" comment="no assign found for given stmt#">39</id><querystr><![CDATA[assign a; Select a with 12 = a.stmt#]]></querystr>
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
<id ReturnTuple="1" UnnamedVar="1" With="1" CondNum="3" RelNum="0" comment="progline with given number LHS">40</id><querystr><![CDATA[prog_line n; Select n with n = 10]]></querystr>
<stuans>10</stuans>
<correct>10</correct>
<time_taken>4.053000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="1" With="1" CondNum="3" RelNum="0" comment="progline with given number RHS">41</id><querystr><![CDATA[prog_line n; Select n with 25 = n]]></querystr>
<stuans>25</stuans>
<correct>25</correct>
<time_taken>4.245000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="1" With="1" CondNum="3" RelNum="0" comment="no progline for given number">42</id><querystr><![CDATA[prog_line n; Select n with n = 37]]></querystr>
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
</queries>
</test_results>
