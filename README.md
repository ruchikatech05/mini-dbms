# mini-dbms
1.  A program to create files for holding tuples of relations. User should be allowed to create any number of relations. 
2.	Datatypes can be integer, double, char, string, varchar, boolean and date. Format for the date is DD-MM-YYYY.  
3.	Constraints to be included
      Primary Key constraint
      Unique Constraint for any field
      Foreign key constraint
      Not Null constraint
4.	For creating a relation, user will issue command similar to the following command:
mydbms>create table table-name  (attributes followed by their types); There may be constraints as mentioned above. 
5.	For inserting tuples into the relation, user will give command similar to the following command:
mydbms>insert into table-name values (values corresponding to the attributes separated by comma) 
6.   Command for DELETE as in SQL. 
Condition for delete can involve at most one predicate.(You may implement it in more detail if you want.)
7.   Data retrieval command: select statement. 
(a) The from clause based on only one relation
(b) The conditions in where clause can have at most two predicates =, <>, >=, <=, <, > involving any two attributes of a relation connected through “and”, “or”, or “not”


Created a parser which will parse the above commands and give appropriate error messages in case of syntax errors. Use lex and yacc for the same.
