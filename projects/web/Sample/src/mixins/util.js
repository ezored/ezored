export const util = {
    methods: {
        getResponseMessage: function (response, context) {
            if (response) {
                if (response.data && response.data.errors && response.data.errors.length > 0) {
                    let error = response.data.errors[0];
                    return error.messages[0];
                } else if (response.message) {
                    if (response.message == 'validate' && context == '') {
                        return 'Check your form data';
                    } else if (response.message == 'validate' && context == 'login') {
                        return 'Your account information is invalid, check your e-mail and password';
                    }
                }
            }

            return 'Error while process your request, try again!'
        },
        shuffleArray: function (array) {
            for (var i = array.length - 1; i > 0; i--) {
                var j = Math.floor(Math.random() * (i + 1));
                var temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}