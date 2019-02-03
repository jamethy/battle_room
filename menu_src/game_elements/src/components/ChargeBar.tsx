import * as React from "react";

export interface BaseGameElementProps {
    uniqueId: string,
    x: number,
    y: number,
}

export interface ChargeBarProps extends BaseGameElementProps{
    chargePercent: number,
    width: number, // in pixels
}

export class ChargeBar extends React.Component<ChargeBarProps, {}> {

    render() {
        const {uniqueId, chargePercent, width, x, y} = this.props;
        let limitedChargePercent = Math.min(100, Math.max(0, chargePercent));
        let height = width / 15;
        let top = y - height / 2;
        let left = x - width / 2;

        const barStyle: React.CSSProperties = {
            background: 'green',
            position: 'fixed',
            height: height + 'px',
            width: (width * limitedChargePercent / 100) + 'px',
            top: top + 'px',
            left: left + 'px',
        };

        return (
            <div id={`charge-bar-${uniqueId}`} style={barStyle}/>
        );
    }
}
