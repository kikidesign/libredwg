#define DWG_TYPE DWG_TYPE_SPLINE
#include "common.c"

void
api_process (dwg_object *obj)
{
  int error;
  BITCODE_RS flag; /* computed */
  BITCODE_BS scenario; /* 1 spline, 2 bezier */
  BITCODE_BS degree;
  BITCODE_BL splineflags1; /* 2013+: method fit points = 1, CV frame show = 2, closed = 4 */
  BITCODE_BL knotparam;    /* 2013+: Chord = 0, Square root = 1, Uniform = 2, Custom = 15 */
  BITCODE_BD fit_tol;
  BITCODE_3BD beg_tan_vec;
  BITCODE_3BD end_tan_vec;
  BITCODE_B closed_b; /* bit 1 of 70 */
  BITCODE_B periodic; /* bit 2 of 70 */
  BITCODE_B rational; /* bit 3 of 70 */
  BITCODE_B weighted; /* bit 4 of 70 */
  BITCODE_BD knot_tol;
  BITCODE_BD ctrl_tol;
  BITCODE_BS num_fit_pts;
  BITCODE_3DPOINT* fit_pts;
  BITCODE_BL num_knots;
  BITCODE_BD* knots;
  BITCODE_BL num_ctrl_pts;
  Dwg_SPLINE_control_point* ctrl_pts;

  dwg_ent_spline *spline = dwg_object_to_SPLINE (obj);

  CHK_ENTITY_TYPE (spline, SPLINE, flag, RS, flag);
  CHK_ENTITY_TYPE (spline, SPLINE, splineflags1, BL, splineflags1);
  CHK_ENTITY_TYPE (spline, SPLINE, knotparam, BL, knotparam);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, scenario, BS, scenario);
  if (scenario == 0 || scenario > 2)
    fail ("Illegal SPLINE.scenario %d", (int)scenario);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, degree, BS, degree);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, fit_tol, BD, fit_tol);
  CHK_ENTITY_3RD  (spline, SPLINE, beg_tan_vec, beg_tan_vec);
  CHK_ENTITY_3RD  (spline, SPLINE, end_tan_vec, end_tan_vec);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, closed_b, B, closed_b);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, periodic, B, periodic);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, rational, B, rational);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, weighted, B, weighted);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, knot_tol, BD, knot_tol);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, ctrl_tol, BD, ctrl_tol);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, num_fit_pts, BS, num_fit_pts);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, num_knots, BL, num_knots);
  CHK_ENTITY_TYPE_W_OLD (spline, SPLINE, num_ctrl_pts, BL, num_ctrl_pts);

  if (!dwg_dynapi_entity_value (spline, "SPLINE", "fit_pts", &fit_pts, NULL))
    fail ("SPLINE.fit_pts");
  if (!dwg_dynapi_entity_value (spline, "SPLINE", "knots", &knots, NULL))
    fail ("SPLINE.knots");
  if (!dwg_dynapi_entity_value (spline, "SPLINE", "ctrl_pts", &ctrl_pts, NULL))
    fail ("SPLINE.ctrl_pts");

  if (scenario == 1)
    {
      dwg_spline_control_point *cpts;
      double *knots1;
      if (num_fit_pts)
        fail ("SPLINE.num_fit_pts with scenario 1");

      cpts = dwg_ent_spline_get_ctrl_pts (spline, &error);
      if (error)
        fail ("SPLINE.ctrl_pts");
      else
        {
          for (BITCODE_BL i = 0; i < num_ctrl_pts; i++)
            {
              ok ("SPLINE.ctrl_pts[%d]: (%f, %f, %f, %f)", i, cpts[i].x,
                  cpts[i].y, cpts[i].z, cpts[i].w);
              if (memcmp (&ctrl_pts[i], &cpts[i], sizeof (ctrl_pts[i])))
                fail ("SPLINE.ctrl_pts[%d]", i);
            }
        }
      free (cpts);

      knots1 = dwg_ent_spline_get_knots (spline, &error);
      if (error)
        fail ("SPLINE.knots");
      else
        {
          for (BITCODE_BL i = 0; i < num_knots; i++)
            {
              ok ("SPLINE.knots[%d]: %f", i, knots1[i]);
              if (memcmp (&knots[i], &knots1[i], sizeof (double)))
                fail ("SPLINE.knots[%d]", i);
            }
        }
      free (knots1);
    }
  else
    {
      dwg_point_3d *pts;
      if (num_knots)
        fail ("SPLINE.num_knots with scenario 2");
      if (num_ctrl_pts)
        fail ("SPLINE.num_ctrl_pts with scenario 2");

      pts = dwg_ent_spline_get_fit_pts (spline, &error);
      if (error)
        fail ("SPLINE.fit_pts");
      else
        {
          for (BITCODE_BL i = 0; i < num_fit_pts; i++)
            {
              ok ("SPLINE.fit_pts[%d]: (%f, %f, %f)", i, pts[i].x,
                  pts[i].y, pts[i].z);
              if (memcmp (&fit_pts[i], &pts[i], sizeof (fit_pts[i])))
                fail ("SPLINE.fit_pts[%d]", i);
            }
        }
      free (pts);
    }
}