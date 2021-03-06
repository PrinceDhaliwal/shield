//
// Created by malcolm on 27/11/17.
//

#include "TelematicsView.h"

#include <string>
#include <utility>
#include <SkPaint.h>
#include <SkPath.h>
#include <SkCanvas.h>
#include <scarlet/LinearLayout.h>
#include <scarlet/TextView.h>
#include <scarlet/FixedView.h>
#include <SkFontStyle.h>
#include <shield/SHIELD.h>
#include <iostream>

namespace avenger {
namespace reed {

std::shared_ptr<scarlet::TextView> makeText(std::string title) {
  auto textView = std::make_shared<scarlet::TextView>(title);
  textView->setFont("Product Sans", SkFontStyle::Bold());
  textView->setColor(SK_ColorGRAY);
  return textView;
}

std::shared_ptr<scarlet::FixedView> makeMargin(int size) {
  auto view = std::make_shared<scarlet::FixedView>();
  view->setColor(SK_ColorTRANSPARENT);
  view->setRect(SkRect::MakeWH(1, size));
  return view;
}

TelematicsView::TelematicsView(std::shared_ptr<Bot> b) {
  updateView();
}

void TelematicsView::onCreate(SkCanvas *canvas) {
  updateView();
}

void makeBotTelematicsView(std::shared_ptr<scarlet::LinearLayout> layout, PyBot &bot) {

}

void TelematicsView::updateView() {
  auto verticalMargin = makeMargin(20);
  auto smallMargin = makeMargin(10);
  auto linearLayout = std::make_shared<scarlet::LinearLayout>();
  linearLayout->setDirection(scarlet::LinearLayout::Direction::kVertical);
  linearLayout->setWidth(1855 - 1220);

  auto title = makeText("Telematics");
  title->setColor(SK_ColorDKGRAY);
  title->setFontSize(24);
  auto subtitle = makeText("Bots");
  subtitle->setFontSize(20);
  subtitle->setColor(SK_ColorGRAY);

  linearLayout->addChild(makeMargin(25));
  linearLayout->addChild(title);
  linearLayout->addChild(makeMargin(10));
  linearLayout->addChild(subtitle);
  linearLayout->addChild(makeMargin(25));

  auto bots = SHIELD::GetInstance()->reed().getPythonControllers();

  for (auto &bot: bots) {
    makeBotTelematicsView(linearLayout, bot);
    auto title = makeText(std::string("Bot ") + std::to_string(bot.id()));
    title->setFontSize(18);
    title->setColor(SK_ColorBLACK);

    auto subtitle = makeText(std::string("IP: ") + bot.getIP());
    subtitle->setFontSize(14);
    subtitle->setColor(SK_ColorGRAY);

    auto posString = std::string("Position: (")
        + std::to_string(bot.getCurrentLocation().x)
        + ", " + std::to_string(bot.getCurrentLocation().y) + ")";

    auto position = makeText(posString);
    position->setFontSize(14);
    position->setColor(SK_ColorDKGRAY);

    auto velString = std::string("Velocity: (")
          + std::to_string(bot.getCurrentVelocity().vx)
          + ", " + std::to_string(bot.getCurrentVelocity().vy) + ")";

    auto vel = makeText(velString);
    vel->setFontSize(14);
    vel->setColor(SK_ColorDKGRAY);

    linearLayout->addChild(title);
    linearLayout->addChild(makeMargin(10));
    linearLayout->addChild(subtitle);
    linearLayout->addChild(makeMargin(10));
    linearLayout->addChild(position);
    linearLayout->addChild(makeMargin(10));
    linearLayout->addChild(vel);
    linearLayout->addChild(makeMargin(30));
  }

  linearLayout->getLayoutParams()->setX(getLayoutParams()->getX());
  linearLayout->getLayoutParams()->setY(getLayoutParams()->getY());
  linearLayout->updateLayout();

  linearLayout->setName("TelematicsLayout");
  getLayoutParams()->setWidth(linearLayout->getLayoutParams()->getWidth());
  getLayoutParams()->setHeight(linearLayout->getLayoutParams()->getHeight());
  setRootView(linearLayout);
}

void TelematicsView::setWidth(Scalar width) {
  getLayoutParams()->setWidth(width);
  updateView();
}

void TelematicsView::setHeight(Scalar height) {
  getLayoutParams()->setHeight(height);
  updateView();
}

}
}