//
// Copyright (C) 2016 OpenSim Ltd
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
//

#include "ProgressMeterFigure.h"
#include "inet/common/INETUtils.h"

//TODO namespace inet { -- for the moment commented out, as OMNeT++ 5.0 cannot instantiate a figure from a namespace
using namespace inet;

Register_Class(ProgressMeterFigure);

#if OMNETPP_VERSION >= 0x500

static const char *PKEY_BACKGROUND_COLOR = "backgroundColor";
static const char *PKEY_STRIP_COLOR = "stripColor";
static const char *PKEY_CORNER_RADIUS = "cornerRadius";
static const char *PKEY_BORDER_WIDTH = "borderWidth";
static const char *PKEY_MIN_VALUE = "minValue";
static const char *PKEY_MAX_VALUE = "maxValue";
static const char *PKEY_TEXT = "text";
static const char *PKEY_TEXT_FONT = "textFont";
static const char *PKEY_TEXT_COLOR = "textColor";
static const char *PKEY_LABEL = "label";
static const char *PKEY_LABEL_FONT = "labelFont";
static const char *PKEY_LABEL_COLOR = "labelColor";
static const char *PKEY_INITIAL_VALUE = "initialValue";
static const char *PKEY_POS = "pos";
static const char *PKEY_SIZE = "size";
static const char *PKEY_ANCHOR = "anchor";
static const char *PKEY_BOUNDS = "bounds";

ProgressMeterFigure::ProgressMeterFigure(const char *name) : cGroupFigure(name)
{
    addChildren();
}

cFigure::Color ProgressMeterFigure::getBackgroundColor() const
{
    return backgroundFigure->getFillColor();
}

void ProgressMeterFigure::setBackgroundColor(cFigure::Color color)
{
    backgroundFigure->setFillColor(color);
}

cFigure::Color ProgressMeterFigure::getStripColor() const
{
    return stripFigure->getFillColor();
}

void ProgressMeterFigure::setStripColor(cFigure::Color color)
{
    stripFigure->setFillColor(color);
}

double ProgressMeterFigure::getCornerRadius() const
{
    return backgroundFigure->getCornerRx();
}

void ProgressMeterFigure::setCornerRadius(double radius)
{
    backgroundFigure->setCornerRadius(radius);
    stripFigure->setCornerRadius(radius);
    borderFigure->setCornerRadius(radius);
}

double ProgressMeterFigure::getBorderWidth() const
{
    return borderFigure->getLineWidth();
}

void ProgressMeterFigure::setBorderWidth(double width)
{
    borderFigure->setLineWidth(width);
}

const char *ProgressMeterFigure::getText() const
{
    return textFormat.c_str();
}

void ProgressMeterFigure::setText(const char *text)
{
    textFormat = text;
    refresh();
}

cFigure::Font ProgressMeterFigure::getTextFont() const
{
    return valueFigure->getFont();
}

void ProgressMeterFigure::setTextFont(cFigure::Font font)
{
    valueFigure->setFont(font);
}

cFigure::Color ProgressMeterFigure::getTextColor() const
{
    return valueFigure->getColor();
}

void ProgressMeterFigure::setTextColor(cFigure::Color color)
{
    valueFigure->setColor(color);
}

const char *ProgressMeterFigure::getLabel() const
{
    return labelFigure->getText();
}

void ProgressMeterFigure::setLabel(const char *text)
{
    labelFigure->setText(text);
}

cFigure::Font ProgressMeterFigure::getLabelFont() const
{
    return labelFigure->getFont();
}

void ProgressMeterFigure::setLabelFont(cFigure::Font font)
{
    labelFigure->setFont(font);
}

cFigure::Color ProgressMeterFigure::getLabelColor() const
{
    return labelFigure->getColor();
}

void ProgressMeterFigure::setLabelColor(cFigure::Color color)
{
    labelFigure->setColor(color);
}

cFigure::Rectangle ProgressMeterFigure::getBounds() const
{
    return borderFigure->getBounds();
}

void ProgressMeterFigure::setBounds(Rectangle bounds)
{
    borderFigure->setBounds(bounds);
    layout();
    refresh();
}

double ProgressMeterFigure::getMinValue() const
{
    return min;
}

void ProgressMeterFigure::setMinValue(double value)
{
    min = value;
    refresh();
}

double ProgressMeterFigure::getMaxValue() const
{
    return max;
}

void ProgressMeterFigure::setMaxValue(double value)
{
    max = value;
    refresh();
}

void ProgressMeterFigure::parse(cProperty *property)
{
    cGroupFigure::parse(property);

    setBounds(parseBounds(property));

    const char *s;
    if ((s = property->getValue(PKEY_BACKGROUND_COLOR)) != nullptr)
        setBackgroundColor(parseColor(s));
    if ((s = property->getValue(PKEY_STRIP_COLOR)) != nullptr)
        setStripColor(parseColor(s));
    if ((s = property->getValue(PKEY_CORNER_RADIUS)) != nullptr)
        setCornerRadius(utils::atod(s));
    if ((s = property->getValue(PKEY_BORDER_WIDTH)) != nullptr)
        setBorderWidth(utils::atod(s));
    if ((s = property->getValue(PKEY_MIN_VALUE)) != nullptr)
        setMinValue(utils::atod(s));
    if ((s = property->getValue(PKEY_MAX_VALUE)) != nullptr)
        setMaxValue(utils::atod(s));
    if ((s = property->getValue(PKEY_TEXT)) != nullptr)
        setText(s);
    if ((s = property->getValue(PKEY_TEXT_FONT)) != nullptr)
        setTextFont(parseFont(s));
    if ((s = property->getValue(PKEY_TEXT_COLOR)) != nullptr)
        setTextColor(parseColor(s));
    if ((s = property->getValue(PKEY_LABEL)) != nullptr)
        setLabel(s);
    if ((s = property->getValue(PKEY_LABEL_FONT)) != nullptr)
        setLabelFont(parseFont(s));
    if ((s = property->getValue(PKEY_LABEL_COLOR)) != nullptr)
        setLabelColor(parseColor(s));
    if ((s = property->getValue(PKEY_INITIAL_VALUE)) != nullptr)
        setValue(0, simTime(), utils::atod(s));
}

const char **ProgressMeterFigure::getAllowedPropertyKeys() const
{
    static const char *keys[32];
    if (!keys[0]) {
        const char *localKeys[] = {
            PKEY_BACKGROUND_COLOR, PKEY_STRIP_COLOR, PKEY_CORNER_RADIUS, PKEY_BORDER_WIDTH,
            PKEY_MIN_VALUE, PKEY_MAX_VALUE, PKEY_TEXT, PKEY_TEXT_FONT, PKEY_TEXT_COLOR, PKEY_LABEL,
            PKEY_LABEL_FONT, PKEY_LABEL_COLOR, PKEY_INITIAL_VALUE, PKEY_POS, PKEY_SIZE, PKEY_ANCHOR,
            PKEY_BOUNDS, nullptr
        };
        concatArrays(keys, cGroupFigure::getAllowedPropertyKeys(), localKeys);
    }
    return keys;
}

void ProgressMeterFigure::layout()
{
    Rectangle bounds = borderFigure->getBounds();
    stripFigure->setBounds(bounds);
    backgroundFigure->setBounds(bounds);

    valueFigure->setPosition(Point(bounds.x + bounds.width / 2, bounds.y + bounds.height / 2));
    labelFigure->setPosition(Point(bounds.x + bounds.width / 2, bounds.y + bounds.height));
}

void ProgressMeterFigure::addChildren()
{
    borderFigure = new cRectangleFigure("border");
    stripFigure = new cRectangleFigure("strip");
    backgroundFigure = new cRectangleFigure("background");
    valueFigure = new cTextFigure("value");
    labelFigure = new cTextFigure("label");

    backgroundFigure->setOutlined(false);
    backgroundFigure->setFilled(true);
    backgroundFigure->setFillColor(Color("#b8afa6"));

    stripFigure->setOutlined(false);
    stripFigure->setFilled(true);
    stripFigure->setFillColor(Color("lightblue"));

    borderFigure->setOutlined(true);
    borderFigure->setFilled(false);
    borderFigure->setLineWidth(2);

    valueFigure->setAnchor(ANCHOR_CENTER);
    labelFigure->setAnchor(ANCHOR_N);

    addFigure(backgroundFigure);
    addFigure(stripFigure);
    addFigure(borderFigure);
    addFigure(valueFigure);
    addFigure(labelFigure);
}

void ProgressMeterFigure::setValue(int series, simtime_t timestamp, double newValue)
{
    ASSERT(series == 0);
    // Note: we currently ignore timestamp
    if (value != newValue) {
        value = newValue;
        refresh();
    }
}

void ProgressMeterFigure::refresh()
{
    // adjust strip
    double stripValue = std::isnan(value) ? min : std::max(min, std::min(max, value));
    cFigure::Rectangle bounds = borderFigure->getBounds();
    bounds.width = bounds.width * (stripValue - min) / (max - min);
    stripFigure->setBounds(bounds);

    // update displayed number
    if (std::isnan(value))
        valueFigure->setText("");
    else {
        char buf[32];
        double percent = (value - min) / (max - min) * 100;
        sprintf(buf, getText(), value, percent);
        if (value < min || value > max)
            strcat(buf, "*");
        valueFigure->setText(buf);
    }
}

#endif    // omnetpp 5

// } // namespace inet

