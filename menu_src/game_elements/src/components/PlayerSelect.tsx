import * as React from "react";
import {BaseGameElement, BaseGameElementProps} from "./BaseGameElement";
import {ChargeBar} from "./ChargeBar";

export interface PlayerSelectProps extends BaseGameElementProps {
    playerWidth: number;
    playerHeight: number;
    jumpCharge: number;
    gunCharge: number;
}

export class PlayerSelect extends BaseGameElement<PlayerSelectProps, {}> {
    render() {

        const {uniqueId, x, y, playerHeight, playerWidth, jumpCharge, gunCharge} = this.props;

        let chargeBars = [];
        if (jumpCharge > 0) {
            chargeBars.push(<ChargeBar charge={jumpCharge} width={playerWidth * 0.8} type={'JumpCharge'}/>);
        }
        if (gunCharge > 0) {
            chargeBars.push(<ChargeBar charge={gunCharge} width={playerWidth * 0.8} type={'GunCharge'}/>);
        }

        let playerRadius = Math.sqrt(playerHeight * playerHeight + playerWidth * playerWidth);
        let top = y + playerRadius / 2;
        let left = x - playerWidth / 2;

        const playerSelectStyle: React.CSSProperties = {
            position: 'fixed',
            top: top + 'px',
            left: left + 'px',
        };

        return (
            <div id={`player-select-${uniqueId}`} style={playerSelectStyle}>
                {...chargeBars}
            </div>
        );
    }
}
