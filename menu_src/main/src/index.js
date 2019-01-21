function component() {
    let element = document.createElement('div');

    const myVar = 34;

    // Lodash, currently included via a script, is required for this line to work
    element.innerHTML = ['Hello', 'webpack', `My var: ${myVar}`].join(' ');

    return element;
}

document.body.appendChild(component());
