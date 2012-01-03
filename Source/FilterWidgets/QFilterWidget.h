/*
 * QFilterWidget.h
 *
 *  Created on: Dec 30, 2011
 *      Author: mjackson
 */

#ifndef QFILTERWIDGET_H_
#define QFILTERWIDGET_H_

#include <QtGui/QFrame>
#include <QtGui/QGroupBox>

#include "DREAM3DLib/Common/AbstractFilter.h"



#define FILTER_PROPERTY_WRAPPER(type, name, filter_var)\
void set##name(type v) { filter_var->set##name(v); }\
type get##name() { return filter_var->get##name(); }\





class QFilterWidget : public QGroupBox
{
    Q_OBJECT;
  public:
    QFilterWidget(QWidget* parent = NULL);
    virtual ~QFilterWidget();

    virtual void setupGui();

    virtual AbstractFilter::Pointer getFilter();

   public slots:

     virtual void updateFilterValues();
     void updateQLineEditDoubleValue();
     void updateQLineEditIntValue();

  protected:

  private:
    QFilterWidget(const QFilterWidget&); // Copy Constructor Not Implemented
    void operator=(const QFilterWidget&); // Operator '=' Not Implemented

};


#endif /* QFILTERWIDGET_H_ */
