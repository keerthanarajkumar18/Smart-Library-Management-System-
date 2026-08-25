#include "Library.h"
#include "LibraryService.h"
#include "LibraryApplication.h"
#include "Database.h"
#include "DatabaseSchema.h"

int main()
{
    Database database("library.db");

    DatabaseSchema::createTables(database);

    BookRepository bookRepository(database);

    Library library;

    library.setBookRepository(bookRepository);

    library.loadBooks(
        bookRepository.findAll()
    );

    LibraryService service(library);

    LibraryApplication application(service);

    application.run();

    return 0;
}
