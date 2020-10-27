ISSUE 1 RAM :

Fixed the issue that the system was using too much ram.
You will see in the reports package. The changes made are in the
ReportImpl , Report Storage and the FEAAFacade classes.
In the ReportImpl constructor, there is logic which checks whether
the value being put in for the report exists within the ReportStorage class.
If it does not it gets added into this Storage class.
Additionally, if it does exist instead of using the given values in the
ReportImpl constructor, the values from the ReportStorage are used.
In FEEAFacade modifications to the getAllReports method have been made.
Instead of returning a reports list from the database it instead returns the
list of reports stored in the ReportStorage class. If this list is empty, then
the reports are first stored from the database.


ISSUE 2 CLASSLOAD:

The issue of the class load has been fixed within the ordering package.
In this package you will see 4 abstractions called CriticalOrder,ScheduledOrder,NormalOrder
CriticalScheduledOrder. Within these 4 abstractions an OrderType object is passed in.
The OrderType objects represent the 66 different types of order types.
NewOrderImpl and Order66 are types of OrderType objects. With the bridge implementation
there are at most 70 classes excluding interfaces. 66 OrderType classes and 4 Order type classes.
In the FEEAFacade class, these new Abstractions are called to form Orders in the createOrder
method.


ISSUE 3 ContactHandler Bulkiness.
This issue has been resolved within the handlers package.
A handler has been made for each contact method, splitting up the logic of the
bulky switch statement from before. The contact handler simply now creates a chain
utilising the chain of responsibility pattern and achieves the same logic with
greater readability and extensibility. The finaliseOrder() method in FEAAFacade
has been altered to now form a chain and call the sendInvoice method invoking the
chain in the ContactHandler class.

ISSUE 4 Lag when clients are loaded
The issue of fixing the lag when clients are loaded from the database has been resolved by making
modifications in the clientImpl class and adding the ClientPool class in the threadPools package
and also adding the clientFields package. The clientImpl class now creates a ClientPool within its constructor.
This ClientPool class makes several callable threads which exist in the clientFields package. One thread
for each attribute. As such the retrieval of client attributes now happens concurrently
thus reducing the lag. The process now is almost instantaneous in the CLI.

ISSUE 5 Difficulty in checking for equality in Reports.
The only modification for this issue was made in ReportImpl. The ReportImpl class was made a value objects.
as such all values/attributes were made immutable and the equals method was overriden.
You will see very easy comparisons between two Reports based on their values in NewOrderImpl class
in the setReports method. as opposed to the very large if statement that was originally there.

ISSUE 6 Slow Order Creation process.
The order creation process was slow because of the saveOrder() method in the database. In order to
resolve this issue the UNIT OF WORK pattern was used. The modifications can be seen in the unitOfWork
package. Whenever FeeaFacade made a call to the database, it is now replaced with a call to the OrderRepository
instead. The OrderRepository remembers all modifcations that need to be made to the database
and does this all at once when the user logs out of the system.
This has signficantly reduced time in the order creation process in the ClientPool

ISSUE 7 no multithreading.
One of the major issues with FeeaFacade was that , while slow database operations occured the user Could
do nothing but wait in the CLI. Threadpools have been used (Within the threadPool package, OrderPool has been made.)
When the user logs out, the OrderRepository commits the changes to the database. To do this quickly when committing,
a OrderPool is created. This OrderPool creates a thread for each modification that needs to be made to the database
whether it is adding, removing or modifying orders. As such, while these threads happen in the background
the user can continue to use the CLI and does not have to wait for these changes to the database to finish.
All threads in the OrderPool happen concurrently making all modifications in a very short time.
