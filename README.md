#Vote-Chain: A Blockchain based Electronic Vote Recording System

**Abstract** Electronic voting systems relying on mere relational data manage-
ment systems for the recording and verification of elective choices would allow
elections to evolve into paperless and automated processes that replace the need
for manual counting, sorting, and verification of ballot papers. But databases
such as MySQL, mongo DB, SQLite and other relational databases are just a
partial solution because they do not provide proper security and are not tamper
proof. Once an Attacker has access to such an DB he owns every aspect of it
and can change it per his will.

Apart from this E-Voting systems that are based on DBMS require client software
for the management of databases, and certain front end entry point software
such as web applications or local desktop applications that are responsible
to capture and store an elective choice. The problem with such a scenario
materializes once we realize the one-sided focus in design and architecture of
these E-Voting systems, a failure to capture, acknowledge and utilize important
transaction aspects and characteristics of incoming and outgoing transactions
i.e. missing transaction protocols for single votes that have no current origin
or destination association.

A blockchain version of Electronic Vote Recording Systems can provide a solution
and merge the two systems into one by storing elective choices
within transactions.

##Proposal
I propose an approach that transforms bitcoins current asset transaction man-
agement design into an electronic peer 2 peer vote recording system where the
network manages and secures transactions by hashing them into an evolving
chain of “hash-based proof-of-work”, additionally I will introduce a new feature
that includes Token-Transition Certificates into transactions which can take on
the role of receipts. All of these aspects together will form a public record that
cannot be changed without redoing the proof of work for all elements in the
chain including our Token-Transition Certificates.