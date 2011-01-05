/*
 * Xournal++
 *
 * Saves a document
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */


#ifndef __SAVEHANDLER_H__
#define __SAVEHANDLER_H__

#include "../util/OutputStream.h"
class XmlNode;

class SaveHandler {
public:
	SaveHandler();
	virtual ~SaveHandler();

public:
	void prepareSave(Document * doc);
	void saveTo(OutputStream * out, String filename);

private:
	void visitPage(XmlNode * root, XojPage * p, Document * doc, int id);
	String getSolidBgStr(BackgroundType type);
	String getColorStr(int c);
	void visitLayer(XmlNode * page, Layer * l);

private:
	XmlNode * root;
	bool firstPdfPageVisited;
	int attachBgId;

	GList * backgroundImages;
};

#endif /* __SAVEHANDLER_H__ */
