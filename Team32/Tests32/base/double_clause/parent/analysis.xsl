<?xml-stylesheet type="text/xsl" href="analysis.xsl"?>
<test_results>
<info>
<name>autotester</name><parsing_time_taken>5.848000</parsing_time_taken>
</info>
<queries>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="select: [stmt (parent)], no link, match">1</id><querystr><![CDATA[assign a; stmt s1, s2; Select s1 such that Parent(s1, s2) pattern a(_, _"1"_)]]></querystr>
<stuans>17,19,22,25,28,30,34,37,39,40,48,5,50,52,54,60,63,7</stuans>
<correct>5,7,17,19,22,25,28,30,34,37,39,40,48,50,52,54,60,63</correct>
<time_taken>7.643000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="select: [stmt (child)], no link, match">2</id><querystr><![CDATA[assign a; stmt s1, s2; Select s2 such that Parent(s1, s2) pattern a(_, _"1"_)]]></querystr>
<stuans>10,11,18,20,23,26,27,28,29,30,31,35,38,39,40,41,42,43,44,45,49,51,53,55,56,57,58,59,6,60,61,62,63,64,7,8,9</stuans>
<correct>6,7,8,9,10,11,18,20,23,26,27,28,29,30,31,35,38,39,40,41,42,43,44,45,49,51,53,55,56,57,58,59,60,61,62,63,64</correct>
<time_taken>3.326000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="select: [variable], no link, match">3</id><querystr><![CDATA[assign a; stmt s1, s2; variable v; Select v such that Parent(s1, s2) pattern a(v, _"1"_)]]></querystr>
<stuans>i,k,m,n,t,x,z</stuans>
<correct>x,z,i,t,m,n,k</correct>
<time_taken>3.467000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="select: [assign], no link, match">4</id><querystr><![CDATA[assign a; stmt s1, s2; variable v; Select a such that Parent(s1, s2) pattern a(_, _"1"_)]]></querystr>
<stuans>11,18,20,23,26,29,35,41,47,49,51,53,55,59,6,8</stuans>
<correct>6,8,11,18,20,23,26,29,35,41,47,49,51,53,55,59</correct>
<time_taken>3.360000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="select: [stmt (parent)], no link, no match">5</id><querystr><![CDATA[assign a; stmt s1, s2; Select s1 such that Parent(s1, s2) pattern a(_, _"y + k"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.534000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="select: [stmt (child)], no link, no match">6</id><querystr><![CDATA[assign a; stmt s1, s2; Select s2 such that Parent(s1, s2) pattern a(_, _"y + k"_)]]></querystr>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="select: [variable], no link, no match">7</id><querystr><![CDATA[assign a; stmt s1, s2; Select v such that Parent(s1, s2) pattern a(v, _"y + k"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.238000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="select: [assign], no link, no match">8</id><querystr><![CDATA[assign a; stmt s1, s2; Select a such that Parent(s1, s2) pattern a(_, _"y + k"_)]]></querystr>
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
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="select: [stmt], link: [assign], match">9</id><querystr><![CDATA[assign a; stmt s; Select s such that Parent(s, a) pattern a(_, _"x"_)]]></querystr>
<stuans>30,5,7</stuans>
<correct>5,7,30</correct>
<time_taken>3.503000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="select: [assign], link: [assign], match">10</id><querystr><![CDATA[assign a; stmt s; Select a such that Parent(s, a) pattern a(_, _"x"_)]]></querystr>
<stuans>10,31,6,8,9</stuans>
<correct>6,8,9,10,31</correct>
<time_taken>3.409000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="1" Pattern="1" SuchThat="1" CondNum="5" RelNum="1" comment="select: [variable], link: [assign], match">11</id><querystr><![CDATA[assign a; stmt s; variable v; Select v such that Parent(s, a) pattern a(v, _"x"_)]]></querystr>
<stuans>p,x,y,z</stuans>
<correct>x,z,y,p</correct>
<time_taken>3.936000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="select: [stmt], link: [assign], no match">12</id><querystr><![CDATA[assign a; stmt s; Select s such that Parent(s, a) pattern a(_, _"y + k"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.541000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="3" Pattern="1" SuchThat="1" CondNum="7" RelNum="1" comment="select: [assign], link: [assign], no match">13</id><querystr><![CDATA[assign a; stmt s; Select a such that Parent(s, a) pattern a(_, _"y + k"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.358000</time_taken>
<failed>
<missing>none</missing>
<additional></additional>
<summary>
<expected>1</expected>
<matched>0</matched>
<missing>1</missing>
<additional>0</additional>
</summary>
</failed>
</query>
<query>
<id ReturnTuple="1" Parent="1" UnnamedVar="2" Pattern="1" SuchThat="1" CondNum="6" RelNum="1" comment="select: [variable], link: [assign], no match">14</id><querystr><![CDATA[assign a; stmt s; variable v; Select v such that Parent(s, a) pattern a(v, _"y + k"_)]]></querystr>
<stuans></stuans>
<correct>none</correct>
<time_taken>3.411000</time_taken>
<failed>
<missing>none</missing>
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
