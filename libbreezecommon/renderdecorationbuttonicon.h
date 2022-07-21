#ifndef BREEZE_RENDERDECORATIONBUTTONICON_H
#define BREEZE_RENDERDECORATIONBUTTONICON_H

/*
 * SPDX-FileCopyrightText: 2021 Paul A McAuley <kde@paulmcauley.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#include "breezecommon_export.h"
#include "breezesettings.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QPainterPath>
#include <memory>

namespace Breeze
{

/**
 * @brief Base Class to render decoration button icons in style set by EnumButtonIconStyle.
 *        Rendering is to be performed on a QPainter object with an 18x18 reference window.
 *        Co-ordinates relative to top-left.
 *        To be used as common code base across both kdecoration and kstyle.
 */
class BREEZECOMMON_EXPORT RenderDecorationButtonIcon18By18
{
public:
    /**
     * @brief Factory to return a pointer to a new inherited object to render in the specified style.
     * @param internalSettings An InternalSettingsPtr from the Window decoration config
     * @param painter A QPainter object already initialised with an 18x18 reference window and pen.
     * @param notInTitlebar Indicates that button is not to be drawn in the title bar, but somewhere else in the UI -- ususally means will be smaller
     * @param boldButtonIcons When in titlebar this will draw bolder button icons if true
     * @param iconWidth the unscaled icon width -- used only when the system icon theme is used
     * @param devicePixelRatio the device pixel ratio (set also for X11 from ysstem scale factor) -- only used for when system icon theme is used
     * @param smallSpacing used to scale on both X11 and Wayland -- on Wayland is a constant
     * @param iconScaleFactor the amount this icon will be sized (excluding dpr/smallSpacing due to screen scaling)
     * @return std::unique_ptr< Breeze::RenderDecorationButtonIcon18By18, std::default_delete< Breeze::RenderDecorationButtonIcon18By18 > > Pointer to a new
     * sub-style object.
     */
    static std::unique_ptr<RenderDecorationButtonIcon18By18> factory(const QSharedPointer<InternalSettings> internalSettings,
                                                                     QPainter *painter,
                                                                     const bool notInTitlebar = false,
                                                                     const bool boldButtonIcons = false,
                                                                     const qreal iconWidth = 18,
                                                                     qreal devicePixelRatio = 1,
                                                                     int smallSpacing = 2,
                                                                     qreal iconScaleFactor = 1);

    virtual ~RenderDecorationButtonIcon18By18();

    virtual void renderCloseIcon();
    virtual void renderMaximizeIcon();
    virtual void renderRestoreIcon();
    virtual void renderMinimizeIcon();
    virtual void renderPinnedOnAllDesktopsIcon();
    virtual void renderPinOnAllDesktopsIcon();
    virtual void renderShadeIcon();
    virtual void renderUnShadeIcon();
    virtual void renderKeepBehindIcon();
    virtual void renderKeepInFrontIcon();
    virtual void renderApplicationMenuIcon();
    virtual void renderContextHelpIcon();

protected:
    /**
     * @brief Constructor
     *
     * @param internalSettings An InternalSettingsPtr from the Window decoration config
     * @param painter A QPainter object already initialised with an 18x18 reference window and pen.
     * @param notInTitlebar Indicates that button is not to be drawn in the title bar, but somewhere else in the UI -- usually means will be smaller
     * @param boldButtonIcons When in titlebar this will draw bolder button icons if true
     * @param iconWidth the unscaled icon width -- used only when the system icon theme is used
     * @param devicePixelRatio the device pixel ratio (set also for X11 from ysstem scale factor) -- only used for when system icon theme is used
     * @param smallSpacing used to scale on both X11 and Wayland -- on Wayland is a constant
     * @param iconScaleFactor the amount this icon will be sized (excluding dpr/smallSpacing due to screen scaling)
     */
    RenderDecorationButtonIcon18By18(QPainter *painter,
                                     const bool notInTitlebar,
                                     const bool boldButtonIcons,
                                     const qreal devicePixelRatio,
                                     const int smallSpacing,
                                     const bool iconScaleFactor);

    /**
     * @brief Initialises pen to standardise cap and join styles.
     * No brush is normal for Breeze's simple outline style.
     */
    virtual void initPainter();

    /**
     *@brief Multiplies the pen width by the bolding factor, and rounds it. Also returns whether the integer-rounded bold pen with is an even or odd number of
     *pixels This is useful for pixel alignment
     *
     *@param penWidth The input pen width
     *@param outputRoundedPenWidth The output pen width, factored by boldingFactor, and rounded
     *@param boldingFactor Optional bolding factor. Set to 1 for no bolding
     */
    bool roundedPenWidthIsOdd(const qreal &penWidth, int &outputRoundedPenWidth, const qreal boldingFactor);

    QPainter *painter;
    QPen pen;
    bool notInTitlebar;
    bool boldButtonIcons;
    qreal m_devicePixelRatio;
    int m_smallSpacing;
    qreal m_iconScaleFactor;
};

}

#endif
