import * as React from "react";
import {PlayerSelect} from "./PlayerSelect";
import {getGameElements, GameElement} from "../GameElementsAppCalls";

export interface GameElementsContainerProps {
}

interface GameElementsContainerState {
    gameElements: GameElement[],
}

function mapGameElement(element: GameElement): React.ReactElement<any> {
    switch (element.type) {
        case 'PlayerSelect':
            return <PlayerSelect {...element.props} />;
        default:
            return <div {...element.props} style={{color: 'white'}}>Unknown game element</div>;
    }
}

export class GameElementsContainer extends React.Component<GameElementsContainerProps, GameElementsContainerState> {

    private refreshInterval: number;

    constructor(props: GameElementsContainerState) {
        super(props);

        this.state = {
            gameElements: []
        };
    }

    componentWillMount() {
        this.refreshInterval = setInterval(() => getGameElements((gameElements) => {
            this.setState({gameElements});
        }), 10);
    }

    componentWillUnmount() {
        clearInterval(this.refreshInterval);
    }

    render() {

        const {gameElements} = this.state;

        return (
            <div>
                {gameElements.map(mapGameElement)}
            </div>
        );

    }
}
