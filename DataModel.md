> # Data model design #
  * Make the data model classes as simple as possible. Their key responsibility is just saving data. Implement the application logic in the visitor class. Use the visitor pattern at runtime to combine the data and logic.
  * Save/load objects to/from document at any level. For example, during copy and paste, the selected data can be saved to a document during copy and they can be loaded from the document during paste.
    * Delay the creation of the data model object as late as possible. If the query function of data model object is never called, keep that object to be NULL. Create and initialized it when it is firstly queried.
    * When save the document, don't save the NULL object. When load the document, don't create the objects who don't have data in document. If the subsequent workflow requires the NULL object, create a new one and make the initialization.
  * Support the partial save and load. For example only load the graphic related data.
  * Support delay load.