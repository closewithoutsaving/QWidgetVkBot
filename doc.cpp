#include "doc.h"

Doc::Doc()
{

}

void Doc::docSearch(QString docName)
{
    Request request;
    request.docSearch(docName);
}
