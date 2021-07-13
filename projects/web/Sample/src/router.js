import { createWebHistory, createRouter } from "vue-router";

import Home from '@/components/Home'
import About from '@/components/About'
import NotFound from '@/components/NotFound'

const routes = [
    {
        path: "/",
        name: "Home",
        component: Home,
    },
    {
        path: "/about",
        name: "About",
        component: About,
    },
    {
        path: "/:catchAll(.*)",
        component: NotFound,
    },
];

const router = createRouter({
    history: createWebHistory(),
    routes,
});

export default router;
