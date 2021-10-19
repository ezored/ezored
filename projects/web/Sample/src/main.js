import { createApp } from 'vue'
import router from './router'

import axios from 'axios'
import VueAxios from 'vue-axios'
import App from './App.vue'

import moment from 'moment';

require('@/assets/css/main.scss')

const app = createApp(App)
app.config.globalProperties.$moment = moment

app.use(router)
app.use(VueAxios, axios)
app.mount('#app')
